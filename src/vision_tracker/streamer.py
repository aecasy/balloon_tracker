"""TCP frame streaming helpers for headless OpenCV workflows."""

from __future__ import annotations

import select
import socket
import struct

import cv2
import numpy as np


class FrameServer:
    """Stream OpenCV frames over TCP to a remote client and receive key presses."""

    def __init__(self, port: int):
        self.port = port
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.bind(("0.0.0.0", port))
        self.server_socket.listen(1)
        self.server_socket.setblocking(False)
        self.client_socket = None
        print(f"Streamer listening on port {port}. Waiting for connection...")

    def send_frame(self, frame_name: str, frame: np.ndarray) -> None:
        """Send a single frame over the socket."""
        if self.client_socket is None:
            self._accept_client()
            if self.client_socket is None:
                return

        try:
            ok, buffer = cv2.imencode(".jpg", frame, [cv2.IMWRITE_JPEG_QUALITY, 85])
            if not ok:
                return

            data = buffer.tobytes()
            name_bytes = frame_name.encode("utf-8")
            header = struct.pack("<H I", len(name_bytes), len(data))

            _, writable, _ = select.select([], [self.client_socket], [], 0.01)
            if writable:
                self.client_socket.sendall(header + name_bytes + data)
        except (ConnectionResetError, BrokenPipeError, socket.error):
            print("Client disconnected.")
            self.client_socket.close()
            self.client_socket = None

    def get_key(self) -> int:
        """Return a key press from the client, or -1 when no key is available."""
        if self.client_socket is None:
            self._accept_client()
            return -1

        try:
            readable, _, _ = select.select([self.client_socket], [], [], 0.001)
            if readable:
                key_data = self.client_socket.recv(4)
                if not key_data:
                    self.client_socket.close()
                    self.client_socket = None
                    return -1
                return struct.unpack("<i", key_data)[0]
        except (ConnectionResetError, BlockingIOError, socket.error):
            pass
        return -1

    def close(self) -> None:
        if self.client_socket:
            self.client_socket.close()
        self.server_socket.close()

    def _accept_client(self) -> None:
        try:
            client, addr = self.server_socket.accept()
            client.setblocking(False)
            self.client_socket = client
            print(f"Streamer connected to {addr}")
        except BlockingIOError:
            pass


class FrameClient:
    """Connect to a FrameServer, display frames, and send keys back."""

    def __init__(self, host: str, port: int):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((host, port))
        print(f"Connected to streamer at {host}:{port}")

    def run(self) -> None:
        try:
            while True:
                header_data = self._recv_all(6)
                if not header_data:
                    break

                name_len, data_len = struct.unpack("<H I", header_data)

                name_bytes = self._recv_all(name_len)
                if not name_bytes:
                    break
                name = name_bytes.decode("utf-8")

                frame_data = self._recv_all(data_len)
                if not frame_data:
                    break

                buffer = np.frombuffer(frame_data, dtype=np.uint8)
                frame = cv2.imdecode(buffer, cv2.IMREAD_COLOR)
                if frame is not None:
                    cv2.imshow(name, frame)

                key = cv2.waitKey(1)
                if key != -1:
                    self.client_socket.sendall(struct.pack("<i", key))
        except KeyboardInterrupt:
            print("\nViewer stopped by user.")
        except ConnectionResetError:
            print("\nServer closed connection.")
        finally:
            self.client_socket.close()
            cv2.destroyAllWindows()

    def _recv_all(self, byte_count: int) -> bytes:
        data = bytearray()
        while len(data) < byte_count:
            packet = self.client_socket.recv(byte_count - len(data))
            if not packet:
                return b""
            data.extend(packet)
        return bytes(data)
