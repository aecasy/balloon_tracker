#!/usr/bin/env python3
"""Serve Pi camera frames to a remote CV/tuning client.

Runs on the Pi. Streams JPEG frames over TCP and applies camera-control updates
(exposure, gain, AWB, focus, framerate) sent back by the client, so the mask,
tracker, and tuning GUI can run on a remote machine at full local speed.

Protocol (lock-step request/response, one frame per round trip):
  client -> server : uint32 length + JSON camera-controls (may be "{}")
  server -> client : uint32 length + JPEG bytes
"""

from __future__ import annotations

import argparse
import json
import socket
import struct
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

import cv2

from vision_tracker.camera import CameraConfig, PiCamera
from vision_tracker.config import default_config_path, load_app_config


def build_camera_config(cfg) -> CameraConfig:
    return CameraConfig(
        width=cfg.camera.width,
        height=cfg.camera.height,
        raw_width=cfg.camera.raw_width,
        raw_height=cfg.camera.raw_height,
        pixel_format=cfg.camera.pixel_format,
        focus=cfg.camera.focus,
        lens_position=cfg.camera.lens_position,
        awb_mode=cfg.camera.awb_mode,
        exposure_time=cfg.camera.exposure_time,
        analogue_gain=cfg.camera.analogue_gain,
        min_framerate=cfg.camera.min_framerate,
        framerate=cfg.camera.framerate,
    )


def recv_all(conn: socket.socket, byte_count: int) -> bytes:
    buffer = bytearray()
    while len(buffer) < byte_count:
        packet = conn.recv(byte_count - len(buffer))
        if not packet:
            return b""
        buffer.extend(packet)
    return bytes(buffer)


def apply_controls(camera: PiCamera, c: dict) -> None:
    camera.set_camera_controls(
        c.get("focus", "continuous"),
        float(c.get("lens_position", 2.0)),
        c.get("awb_mode", "auto"),
        int(c.get("exposure_time", 0)),
        float(c.get("analogue_gain", 0.0)),
        float(c.get("min_framerate", 0.0)),
        c.get("framerate"),
    )


def serve_client(conn: socket.socket, camera: PiCamera, quality: int) -> None:
    last_controls = None
    while True:
        header = recv_all(conn, 4)
        if not header:
            return
        (length,) = struct.unpack("<I", header)
        control_bytes = recv_all(conn, length) if length else b""
        if length and not control_bytes:
            return

        if control_bytes:
            try:
                controls = json.loads(control_bytes.decode("utf-8"))
            except (ValueError, UnicodeDecodeError):
                controls = {}
            if controls and controls != last_controls:
                apply_controls(camera, controls)
                last_controls = controls

        frame = camera.capture_array()
        ok, buffer = cv2.imencode(".jpg", frame, [cv2.IMWRITE_JPEG_QUALITY, quality])
        if not ok:
            continue
        data = buffer.tobytes()
        conn.sendall(struct.pack("<I", len(data)) + data)


def main() -> int:
    parser = argparse.ArgumentParser(description="Stream Pi camera frames to a remote tuning client.")
    parser.add_argument("--config", type=Path, default=default_config_path(PROJECT_ROOT))
    parser.add_argument("--port", type=int, default=5001)
    parser.add_argument("--jpeg-quality", type=int, default=90)
    args = parser.parse_args()

    cfg = load_app_config(args.config.resolve())
    cam_cfg = build_camera_config(cfg)

    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server.bind(("0.0.0.0", args.port))
    server.listen(1)
    print(f"camera stream server listening on :{args.port} ({cam_cfg.width}x{cam_cfg.height})", flush=True)

    with PiCamera(cam_cfg) as camera:
        while True:
            print("waiting for client...", flush=True)
            conn, addr = server.accept()
            conn.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
            print(f"client connected: {addr}", flush=True)
            try:
                serve_client(conn, camera, args.jpeg_quality)
            except (ConnectionResetError, BrokenPipeError, OSError) as exc:
                print(f"client disconnected: {exc}", flush=True)
            finally:
                conn.close()

    return 0


if __name__ == "__main__":
    raise SystemExit(main())
