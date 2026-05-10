#!/usr/bin/env python3
"""Run the green ball tracker from a Raspberry Pi camera."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

import cv2

from vision_tracker.camera import CameraConfig, PiCamera
from vision_tracker.color_detector import HsvRange, create_hsv_mask, parse_hsv_triplet
from vision_tracker.geometry import ImageSize
from vision_tracker.tracker import TargetTracker, TrackerConfig


def main() -> int:
    args = parse_args()

    camera_config = CameraConfig(
        width=args.width,
        height=args.height,
        focus=args.focus,
        lens_position=args.lens_position,
    )
    hsv_range = HsvRange(lower=args.lower_hsv, upper=args.upper_hsv)
    tracker = TargetTracker(
        TrackerConfig(
            min_area=args.min_area,
            min_circularity=args.min_circularity,
            smoothing_alpha=args.smoothing_alpha,
        )
    )
    image_size = ImageSize(width=args.width, height=args.height)

    try:
        with PiCamera(camera_config) as camera:
            while True:
                frame = camera.capture_array()
                mask = create_hsv_mask(
                    frame,
                    hsv_range,
                    open_iterations=args.open_iterations,
                    close_iterations=args.close_iterations,
                    kernel_size=args.kernel_size,
                )
                result = tracker.update(mask, image_size)
                print(result.to_log_line(), flush=True)

                if args.display:
                    display_frame = frame.copy()
                    draw_detection(display_frame, result)
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
    parser.add_argument("--width", type=int, default=640, help="camera image width")
    parser.add_argument("--height", type=int, default=480, help="camera image height")
    parser.add_argument("--lower-hsv", type=parse_hsv_triplet, default=(68, 180, 20), help="lower HSV bound: H,S,V")
    parser.add_argument("--upper-hsv", type=parse_hsv_triplet, default=(88, 255, 255), help="upper HSV bound: H,S,V")
    parser.add_argument("--min-area", type=float, default=300.0, help="minimum contour area in pixels")
    parser.add_argument("--min-circularity", type=float, default=0.55, help="minimum contour circularity from 0 to 1")
    parser.add_argument("--smoothing-alpha", type=float, default=0.35, help="centroid smoothing alpha from 0 to 1")
    parser.add_argument("--kernel-size", type=int, default=5, help="morphology kernel size; use 0 to disable")
    parser.add_argument("--open-iterations", type=int, default=1, help="morphological open iterations")
    parser.add_argument("--close-iterations", type=int, default=2, help="morphological close iterations")
    parser.add_argument("--focus", choices=["continuous", "manual", "none"], default="continuous", help="camera focus mode")
    parser.add_argument("--lens-position", type=float, default=2.0, help="manual focus lens position")
    parser.add_argument("--no-display", dest="display", action="store_false", help="disable OpenCV debug windows")
    parser.set_defaults(display=True)
    return parser.parse_args()


def draw_detection(frame, result) -> None:
    height, width = frame.shape[:2]
    center = (width // 2, height // 2)
    cv2.drawMarker(frame, center, (255, 255, 255), markerType=cv2.MARKER_CROSS, markerSize=20, thickness=1)

    if result.detected and result.centroid is not None:
        target = (int(round(result.centroid.x)), int(round(result.centroid.y)))
        cv2.circle(frame, target, 10, (0, 255, 255), 2)
        cv2.line(frame, center, target, (0, 255, 255), 1)
        cv2.putText(
            frame,
            result.to_log_line(),
            (10, 30),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.55,
            (0, 255, 255),
            2,
            cv2.LINE_AA,
        )


if __name__ == "__main__":
    raise SystemExit(main())
