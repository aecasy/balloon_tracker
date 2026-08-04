"""Network camera client that mirrors the PiCamera interface.

Receives JPEG frames from ``scripts/camera_stream_server.py`` running on the Pi
and forwards camera-control changes back to it, so CV processing and tuning can
run on a remote machine while the physical camera stays on the Pi.
"""

from __future__ import annotations

import json
import socket
import struct
from typing import Optional

import numpy as np


class NetworkCamera:
    """Drop-in replacement for PiCamera backed by a remote frame server."""

    def __init__(self, host: str, port: int) -> None:
        self.host = host
        self.port = port
        self._sock: Optional[socket.socket] = None
        self._pending_controls: Optional[dict] = None

    def __enter__(self) -> "NetworkCamera":
        self.start()
        return self

    def __exit__(self, exc_type, exc, tb) -> None:
        self.stop()

    def start(self) -> None:
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        sock.settimeout(10.0)
        sock.connect((self.host, self.port))
        sock.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
        self._sock = sock

    def stop(self) -> None:
        if self._sock is not None:
            try:
                self._sock.close()
            finally:
                self._sock = None

    def capture_array(self) -> np.ndarray:
        import cv2

        if self._sock is None:
            raise RuntimeError("camera has not been started")

        payload = json.dumps(self._pending_controls or {}).encode("utf-8")
        self._sock.sendall(struct.pack("<I", len(payload)) + payload)
        self._pending_controls = None

        header = self._recv_all(4)
        (length,) = struct.unpack("<I", header)
        data = self._recv_all(length)
        frame = cv2.imdecode(np.frombuffer(data, np.uint8), cv2.IMREAD_COLOR)
        if frame is None:
            raise RuntimeError("failed to decode frame from camera stream")
        return frame

    def set_camera_controls(
        self,
        focus: str,
        lens_position: float,
        awb_mode: str = "auto",
        exposure_time: int = 0,
        analogue_gain: float = 0.0,
        min_framerate: float = 0.0,
        framerate: Optional[float] = None,
    ) -> None:
        self._pending_controls = {
            "focus": focus,
            "lens_position": lens_position,
            "awb_mode": awb_mode,
            "exposure_time": exposure_time,
            "analogue_gain": analogue_gain,
            "min_framerate": min_framerate,
            "framerate": framerate,
        }

    def _recv_all(self, byte_count: int) -> bytes:
        buffer = bytearray()
        while len(buffer) < byte_count:
            packet = self._sock.recv(byte_count - len(buffer))
            if not packet:
                raise ConnectionError("camera stream closed by server")
            buffer.extend(packet)
        return bytes(buffer)
