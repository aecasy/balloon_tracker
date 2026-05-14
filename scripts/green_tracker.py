#!/usr/bin/env python3
"""Run the green ball tracker from a Raspberry Pi camera."""

from __future__ import annotations

import argparse
import json
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

import cv2

from vision_tracker.camera import CameraConfig, PiCamera
from vision_tracker.calibration import default_calibration_path, load_calibration_optional
from vision_tracker.color_detector import create_hsv_mask, parse_hsv_triplet
from vision_tracker.config import default_config_path, load_app_config, with_overrides
from vision_tracker.geometry import ImageSize, calibrated_pixel_to_bearing_degrees
from vision_tracker.tracker import TargetTracker


def main() -> int:
    args = parse_args()
    config_path = args.config.resolve()
    config = load_app_config(config_path)
    config = with_overrides(
        config,
        width=args.width,
        height=args.height,
        focus=args.focus,
        lens_position=args.lens_position,
        lower_hsv=args.lower_hsv,
        upper_hsv=args.upper_hsv,
        min_area=args.min_area,
        min_circularity=args.min_circularity,
        smoothing_alpha=args.smoothing_alpha,
        kernel_size=args.kernel_size,
        open_iterations=args.open_iterations,
        close_iterations=args.close_iterations,
    )

    camera_config = CameraConfig(
        width=config.camera.width,
        height=config.camera.height,
        pixel_format=config.camera.pixel_format,
        focus=config.camera.focus,
        lens_position=config.camera.lens_position,
    )
    tracker = TargetTracker(config.tracker, config.scoring)
    image_size = ImageSize(width=config.camera.width, height=config.camera.height)
    calibration = load_calibration_optional(args.calibration.resolve())

    if calibration is None and not args.allow_uncalibrated:
        raise SystemExit(
            f"Calibration file not found: {args.calibration}. "
            "Run scripts/calibrate_camera.py first or pass --allow-uncalibrated."
        )

    print(f"loaded_config={config_path}", file=sys.stderr, flush=True)
    if calibration is not None:
        print(f"loaded_calibration={args.calibration.resolve()}", file=sys.stderr, flush=True)

    try:
        with PiCamera(camera_config) as camera:
            while True:
                frame = camera.capture_array()
                mask = create_hsv_mask(
                    frame,
                    config.hsv,
                    open_iterations=config.morphology.open_iterations,
                    close_iterations=config.morphology.close_iterations,
                    kernel_size=config.morphology.kernel_size,
                )
                result = tracker.update(mask, image_size, frame=frame, method=args.method)
                yaw_deg, pitch_deg = result_bearing(result, calibration)
                print(format_result(result, yaw_deg, pitch_deg, args), flush=True)

                if args.display:
                    display_frame = frame.copy()
                    draw_detection(display_frame, result, yaw_deg, pitch_deg)
                    cv2.imshow("camera", display_frame)
                    cv2.imshow("mask", mask)
                    if cv2.waitKey(1) & 0xFF == ord("q"):
                        break
    except KeyboardInterrupt:
        pass
    finally:
        cv2.destroyAllWindows()

    return 0


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Track a green ball target with Picamera2 and OpenCV.")
    parser.add_argument(
        "--config",
        type=Path,
        default=default_config_path(PROJECT_ROOT),
        help="tracker JSON config file",
    )
    parser.add_argument("--width", type=int, default=None, help="temporary camera image width override")
    parser.add_argument("--height", type=int, default=None, help="temporary camera image height override")
    parser.add_argument("--lower-hsv", type=parse_hsv_triplet, default=None, help="temporary lower HSV override: H,S,V")
    parser.add_argument("--upper-hsv", type=parse_hsv_triplet, default=None, help="temporary upper HSV override: H,S,V")
    parser.add_argument("--min-area", type=float, default=None, help="temporary minimum contour area override")
    parser.add_argument("--min-circularity", type=float, default=None, help="temporary circularity override from 0 to 1")
    parser.add_argument("--smoothing-alpha", type=float, default=None, help="temporary smoothing alpha override from 0 to 1")
    parser.add_argument("--kernel-size", type=int, default=None, help="temporary morphology kernel size override")
    parser.add_argument("--open-iterations", type=int, default=None, help="temporary morphological open override")
    parser.add_argument("--close-iterations", type=int, default=None, help="temporary morphological close override")
    parser.add_argument("--focus", choices=["continuous", "manual", "none"], default=None, help="temporary focus mode override")
    parser.add_argument("--lens-position", type=float, default=None, help="temporary manual focus lens position override")
    parser.add_argument("--method", choices=["legacy", "scored"], default="legacy", help="candidate selection method")
    parser.add_argument("--log-components", action="store_true", help="include scored component values in output")
    parser.add_argument("--output", choices=["text", "json"], default="text", help="output format for each frame")
    parser.add_argument(
        "--calibration",
        type=Path,
        default=default_calibration_path(PROJECT_ROOT),
        help="camera calibration JSON file",
    )
    parser.add_argument("--allow-uncalibrated", action="store_true", help="run without yaw/pitch if calibration is missing")
    parser.add_argument("--headless", action="store_true", help="disable OpenCV display windows")
    parser.add_argument("--no-display", dest="display", action="store_false", help="disable OpenCV debug windows")
    parser.set_defaults(display=True)
    args = parser.parse_args()
    if args.headless:
        args.display = False
    return args


def result_bearing(result, calibration):
    if not result.detected or result.centroid is None or calibration is None:
        return None, None
    return calibrated_pixel_to_bearing_degrees(result.centroid, calibration)


def format_result(result, yaw_deg, pitch_deg, args) -> str:
    if args.output == "json":
        payload = {
            "timestamp": result.timestamp,
            "method": result.method,
            "detected": result.detected,
            "centroid": None,
            "dx": result.dx,
            "dy": result.dy,
            "area": result.area,
            "circularity": result.circularity,
            "yaw_deg": yaw_deg,
            "pitch_deg": pitch_deg,
        }
        if result.centroid is not None:
            payload["centroid"] = {"x": result.centroid.x, "y": result.centroid.y}
        if hasattr(result, "score"):
            payload["score"] = result.score
        if args.log_components and hasattr(result, "component_scores"):
            payload["components"] = result.component_scores()
        elif args.log_components and hasattr(result, "candidates") and result.detected:
            payload["components"] = {
                "color_fill": result.color_fill,
                "circularity": result.circularity_score,
                "circle_fit": result.circle_fit,
                "relative_area": result.relative_area,
                "enclosing_fill": result.enclosing_fill,
                "solidity": result.solidity,
                "shading": result.shading_score,
            }
        return json.dumps(payload, separators=(",", ":"))

    line = result.to_log_line(include_components=args.log_components)
    line = f"{line} yaw_deg={format_optional_float(yaw_deg)} pitch_deg={format_optional_float(pitch_deg)}"
    return line


def format_optional_float(value) -> str:
    if value is None:
        return "None"
    return f"{value:.2f}"


def draw_detection(frame, result, yaw_deg, pitch_deg) -> None:
    height, width = frame.shape[:2]
    center = (width // 2, height // 2)
    cv2.drawMarker(frame, center, (255, 255, 255), markerType=cv2.MARKER_CROSS, markerSize=20, thickness=1)

    if result.detected and result.centroid is not None:
        target = (int(round(result.centroid.x)), int(round(result.centroid.y)))
        cv2.circle(frame, target, 10, (0, 255, 255), 2)
        cv2.line(frame, center, target, (0, 255, 255), 1)
        cv2.putText(
            frame,
            f"{result.to_log_line()} yaw={format_optional_float(yaw_deg)} pitch={format_optional_float(pitch_deg)}",
            (10, 30),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.55,
            (0, 255, 255),
            2,
            cv2.LINE_AA,
        )


if __name__ == "__main__":
    raise SystemExit(main())
