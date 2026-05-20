import socket
import struct
import cv2
import numpy as np
import select

class FrameServer:
    """Stream OpenCV frames over TCP to a remote client and receive key presses."""
    
    def __init__(self, port: int):
        self.port = port
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        # Allow reuse address so we don't get "Address already in use" if we restart quickly
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.bind(('0.0.0.0', port))
        self.server_socket.listen(1)
        self.server_socket.setblocking(False)
        self.client_socket = None
        print(f"Streamer listening on port {port}. Waiting for connection...")

    def _accept_client(self):
        try:
            client, addr = self.server_socket.accept()
            client.setblocking(False)
            self.client_socket = client
            print(f"Streamer connected to {addr}")
        except BlockingIOError:
            pass

    def send_frame(self, frame_name: str, frame: np.ndarray) -> None:
        """Send a single frame over the socket."""
        if self.client_socket is None:
            self._accept_client()
            if self.client_socket is None:
                return # No client connected yet

        try:
            # Compress the frame
            ret, buffer = cv2.imencode('.jpg', frame, [cv2.IMWRITE_JPEG_QUALITY, 85])
            if not ret:
                return

            data = buffer.tobytes()
            # Send name length, name, data length, data
            name_bytes = frame_name.encode('utf-8')
            header = struct.pack('<H I', len(name_bytes), len(data))
            
            # Use select to ensure socket is writable
            _, writable, _ = select.select([], [self.client_socket], [], 0.01)
            if writable:
                self.client_socket.sendall(header + name_bytes + data)
        except (ConnectionResetError, BrokenPipeError, socket.error):
            print("Client disconnected.")
            self.client_socket.close()
            self.client_socket = None

    def get_key(self) -> int:
        """Non-blocking check for key press from client."""
        if self.client_socket is None:
            self._accept_client()
            return -1
            
        try:
            readable, _, _ = select.select([self.client_socket], [], [], 0.001)
            if readable:
                key_data = self.client_socket.recv(4)
                if not key_data: # Connection closed
                    self.client_socket.close()
                    self.client_socket = None
                    return -1
                return struct.unpack('<i', key_data)[0]
        except (ConnectionResetError, BlockingIOError, socket.error):
            pass
        return -1
        
    def close(self):
        if self.client_socket:
            self.client_socket.close()
        self.server_socket.close()


class FrameClient:
    """Connect to a FrameServer, display frames, and send keys back."""
    
    def __init__(self, host: str, port: int):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((host, port))
        print(f"Connected to streamer at {host}:{port}")

    def run(self):
        try:
            while True:
                # Read header (name length (2) + data length (4))
                header_data = self._recv_all(6)
                if not header_data:
                    break
                    
                name_len, data_len = struct.unpack('<H I', header_data)
                
                # Read name
                name_bytes = self._recv_all(name_len)
                if not name_bytes:
                    break
                name = name_bytes.decode('utf-8')
                
                # Read frame data
                frame_data = self._recv_all(data_len)
                if not frame_data:
                    break
                    
                # Decode frame
                buffer = np.frombuffer(frame_data, dtype=np.uint8)
                frame = cv2.imdecode(buffer, cv2.IMREAD_COLOR)
                
                if frame is not None:
                    cv2.imshow(name, frame)
                    
                key = cv2.waitKey(1)
                # If key was pressed, send it to server
                if key != -1:
                    self.client_socket.sendall(struct.pack('<i', key))
                    
        except KeyboardInterrupt:
            print("\nViewer stopped by user.")
        except ConnectionResetError:
            print("\nServer closed connection.")
        finally:
            self.client_socket.close()
            cv2.destroyAllWindows()

    def _recv_all(self, n: int) -> bytes:
        """Helper to receive exactly n bytes or return empty bytes on EOF."""
        data = bytearray()
        while len(data) < n:
            packet = self.client_socket.recv(n - len(data))
            if not packet:
                return b''
            data.extend(packet)
        return bytes(data)
