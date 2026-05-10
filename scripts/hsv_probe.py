#!/usr/bin/env python3
"""Click on the camera image to print BGR and HSV values."""

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

latest_frame = None


def main() -> int:
    global latest_frame

    parser = argparse.ArgumentParser(description="Sample HSV values by clicking on the camera image.")
    parser.add_argument("--width", type=int, default=640)
    parser.add_argument("--height", type=int, default=480)
    parser.add_argument("--focus", choices=["continuous", "manual", "none"], default="continuous")
    parser.add_argument("--lens-position", type=float, default=2.0)
    args = parser.parse_args()

    config = CameraConfig(
        width=args.width,
        height=args.height,
        focus=args.focus,
        lens_position=args.lens_position,
    )

    cv2.namedWindow("camera")
    cv2.setMouseCallback("camera", handle_mouse_click)

    try:
        with PiCamera(config) as camera:
            while True:
                latest_frame = camera.capture_array()
                cv2.imshow("camera", latest_frame)
                if cv2.waitKey(1) & 0xFF == ord("q"):
                    break
    except KeyboardInterrupt:
        pass
    finally:
        cv2.destroyAllWindows()

    return 0


def handle_mouse_click(event, x, y, flags, param) -> None:
    if event != cv2.EVENT_LBUTTONDOWN or latest_frame is None:
        return

    bgr = latest_frame[y, x]
    hsv_pixel = cv2.cvtColor(latest_frame[y : y + 1, x : x + 1], cv2.COLOR_BGR2HSV)[0, 0]
    print(
        f"x={x} y={y} "
        f"BGR=({int(bgr[0])},{int(bgr[1])},{int(bgr[2])}) "
        f"HSV=({int(hsv_pixel[0])},{int(hsv_pixel[1])},{int(hsv_pixel[2])})",
        flush=True,
    )


if __name__ == "__main__":
    raise SystemExit(main())
