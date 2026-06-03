#!/usr/bin/env python3
"""Connect to a headless Pi to view OpenCV streams and send keystrokes."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

from vision_tracker.streamer import FrameClient


def main() -> int:
    parser = argparse.ArgumentParser(description="View remote OpenCV streams from the Pi.")
    parser.add_argument("--ip", required=True, help="IP address of the Raspberry Pi")
    parser.add_argument("--port", type=int, default=5000, help="Port the Pi is streaming on")
    args = parser.parse_args()

    client = FrameClient(args.ip, args.port)
    client.run()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
