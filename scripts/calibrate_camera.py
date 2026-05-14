#!/usr/bin/env python3
"""Capture checkerboard views and save camera calibration."""

from __future__ import annotations

import argparse
import sys
from datetime import datetime, timezone
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

import cv2
import numpy as np

from vision_tracker.calibration import CalibrationData, default_calibration_path, save_calibration
from vision_tracker.camera import CameraConfig, PiCamera


def main() -> int:
    args = parse_args()
    output_path = args.output.resolve()
    pattern_size = (args.pattern_cols, args.pattern_rows)
    object_template = build_object_points(args.pattern_cols, args.pattern_rows, args.square_size_mm)
    object_points = []
    image_points = []
    last_corners = None
    last_gray_shape = None

    camera_config = CameraConfig(
        width=args.width,
        height=args.height,
        focus=args.focus,
        lens_position=args.lens_position,
    )

    print("Checkerboard calibration")
    print(f"pattern_cols={args.pattern_cols} pattern_rows={args.pattern_rows} square_size_mm={args.square_size_mm}")
    print("Press c to capture a detected board, k to calibrate/save, q to quit.")

    try:
        with PiCamera(camera_config) as camera:
            while True:
                frame = camera.capture_array()
                gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
                found, corners = cv2.findChessboardCorners(gray, pattern_size, None)
                display_frame = frame.copy()

                if found:
                    criteria = (
                        cv2.TERM_CRITERIA_EPS + cv2.TERM_CRITERIA_MAX_ITER,
                        30,
                        0.001,
                    )
                    corners = cv2.cornerSubPix(gray, corners, (11, 11), (-1, -1), criteria)
                    cv2.drawChessboardCorners(display_frame, pattern_size, corners, found)
                    last_corners = corners
                    last_gray_shape = gray.shape[::-1]
                    status = f"found=True samples={len(object_points)}"
                else:
                    status = f"found=False samples={len(object_points)}"

                cv2.putText(
                    display_frame,
                    status,
                    (10, 28),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.7,
                    (0, 255, 255),
                    2,
                    cv2.LINE_AA,
                )
                cv2.imshow("calibration", display_frame)

                key = cv2.waitKey(1) & 0xFF
                if key == ord("c"):
                    if last_corners is None:
                        print("capture_skipped reason=no_checkerboard", flush=True)
                        continue
                    object_points.append(object_template.copy())
                    image_points.append(last_corners.copy())
                    print(f"captured={len(object_points)}", flush=True)
                elif key == ord("k"):
                    if len(object_points) < args.min_samples:
                        print(f"calibration_skipped reason=need_{args.min_samples}_samples have={len(object_points)}", flush=True)
                        continue
                    calibration = calibrate(
                        object_points,
                        image_points,
                        last_gray_shape,
                        args.pattern_cols,
                        args.pattern_rows,
                        args.square_size_mm,
                    )
                    save_calibration(calibration, output_path)
                    print(f"saved_calibration={output_path}", flush=True)
                    print(f"reprojection_error={calibration.reprojection_error:.4f}", flush=True)
                elif key == ord("q"):
                    break
    except KeyboardInterrupt:
        pass
    finally:
        cv2.destroyAllWindows()

    return 0


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Calibrate the Pi camera from checkerboard captures.")
    parser.add_argument("--pattern-cols", type=int, default=6, help="checkerboard inner corners across columns")
    parser.add_argument("--pattern-rows", type=int, default=8, help="checkerboard inner corners across rows")
    parser.add_argument("--square-size-mm", type=float, default=35.8, help="checkerboard square size in millimeters")
    parser.add_argument("--min-samples", type=int, default=15, help="minimum captured views before saving calibration")
    parser.add_argument("--width", type=int, default=640, help="camera image width")
    parser.add_argument("--height", type=int, default=480, help="camera image height")
    parser.add_argument("--focus", choices=["continuous", "manual", "none"], default="continuous", help="camera focus mode")
    parser.add_argument("--lens-position", type=float, default=2.0, help="manual focus lens position")
    parser.add_argument(
        "--output",
        type=Path,
        default=default_calibration_path(PROJECT_ROOT),
        help="calibration JSON output path",
    )
    return parser.parse_args()


def build_object_points(pattern_cols: int, pattern_rows: int, square_size_mm: float) -> np.ndarray:
    object_points = np.zeros((pattern_rows * pattern_cols, 3), np.float32)
    object_points[:, :2] = np.mgrid[0:pattern_cols, 0:pattern_rows].T.reshape(-1, 2)
    object_points *= square_size_mm
    return object_points


def calibrate(
    object_points,
    image_points,
    image_size,
    pattern_cols: int,
    pattern_rows: int,
    square_size_mm: float,
) -> CalibrationData:
    ret, camera_matrix, distortion, rotation_vectors, translation_vectors = cv2.calibrateCamera(
        object_points,
        image_points,
        image_size,
        None,
        None,
    )
    reprojection_error = compute_reprojection_error(
        object_points,
        image_points,
        rotation_vectors,
        translation_vectors,
        camera_matrix,
        distortion,
    )

    return CalibrationData(
        image_width=int(image_size[0]),
        image_height=int(image_size[1]),
        fx=float(camera_matrix[0, 0]),
        fy=float(camera_matrix[1, 1]),
        cx=float(camera_matrix[0, 2]),
        cy=float(camera_matrix[1, 2]),
        distortion_coefficients=[float(value) for value in distortion.ravel()],
        reprojection_error=float(reprojection_error if np.isfinite(reprojection_error) else ret),
        pattern_cols=pattern_cols,
        pattern_rows=pattern_rows,
        square_size_mm=square_size_mm,
        sample_count=len(object_points),
        created_at=datetime.now(timezone.utc).isoformat(),
    )


def compute_reprojection_error(
    object_points,
    image_points,
    rotation_vectors,
    translation_vectors,
    camera_matrix,
    distortion,
) -> float:
    total_error = 0.0
    total_points = 0
    for obj_points, img_points, rvec, tvec in zip(object_points, image_points, rotation_vectors, translation_vectors):
        projected_points, _ = cv2.projectPoints(obj_points, rvec, tvec, camera_matrix, distortion)
        error = cv2.norm(img_points, projected_points, cv2.NORM_L2)
        total_error += error * error
        total_points += len(obj_points)

    if total_points <= 0:
        return 0.0
    return float(np.sqrt(total_error / total_points))


if __name__ == "__main__":
    raise SystemExit(main())
