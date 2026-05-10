#!/usr/bin/env python3
"""Minimal Picamera2 + OpenCV preview."""

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


def main() -> int:
    parser = argparse.ArgumentParser(description="Open a simple live camera preview.")
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

    try:
        with PiCamera(config) as camera:
            while True:
                frame = camera.capture_array()
                cv2.imshow("camera", frame)
                if cv2.waitKey(1) & 0xFF == ord("q"):
                    break
    except KeyboardInterrupt:
        pass
    finally:
        cv2.destroyAllWindows()

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
