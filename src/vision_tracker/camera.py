"""Picamera2 setup helpers."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Optional


CAMERA_MODULE_3_FULL_WIDTH = 4608
CAMERA_MODULE_3_FULL_HEIGHT = 2592
CAMERA_MODULE_3_DEFAULT_WIDTH = 1280
CAMERA_MODULE_3_DEFAULT_HEIGHT = 720
CAMERA_MODULE_3_DEFAULT_RAW_WIDTH = 2304
CAMERA_MODULE_3_DEFAULT_RAW_HEIGHT = 1296
CAMERA_MODULE_3_FAST_WIDTH = 1536
CAMERA_MODULE_3_FAST_HEIGHT = 864
CAMERA_MODULE_3_FAST_FPS = 120.0


@dataclass(frozen=True)
class CameraConfig:
    width: int = CAMERA_MODULE_3_DEFAULT_WIDTH
    height: int = CAMERA_MODULE_3_DEFAULT_HEIGHT
    raw_width: Optional[int] = CAMERA_MODULE_3_DEFAULT_RAW_WIDTH
    raw_height: Optional[int] = CAMERA_MODULE_3_DEFAULT_RAW_HEIGHT
    pixel_format: str = "RGB888"
    focus: str = "continuous"
    lens_position: float = 2.0
    framerate: Optional[float] = None

    def __post_init__(self) -> None:
        if self.width <= 0 or self.height <= 0:
            raise ValueError("camera dimensions must be positive")
        if (self.raw_width is None) != (self.raw_height is None):
            raise ValueError("raw_width and raw_height must be set together")
        if self.raw_width is not None and self.raw_width <= 0:
            raise ValueError("raw_width must be positive")
        if self.raw_height is not None and self.raw_height <= 0:
            raise ValueError("raw_height must be positive")
        if self.focus not in {"continuous", "manual", "none"}:
            raise ValueError("focus must be one of: continuous, manual, none")
        if self.framerate is not None and self.framerate <= 0:
            raise ValueError("framerate must be positive")


class PiCamera:
    """Small wrapper around Picamera2 with lazy imports for non-Pi test runs."""

    def __init__(self, config: CameraConfig) -> None:
        self.config = config
        self._picam2 = None

    def __enter__(self) -> "PiCamera":
        self.start()
        return self

    def __exit__(self, exc_type, exc, tb) -> None:
        self.stop()

    def start(self) -> None:
        from picamera2 import Picamera2

        self._picam2 = Picamera2()
        preview_options = {
            "main": {"size": (self.config.width, self.config.height), "format": self.config.pixel_format}
        }
        if self.config.raw_width is not None and self.config.raw_height is not None:
            preview_options["raw"] = {"size": (self.config.raw_width, self.config.raw_height)}
        if self.config.framerate is not None:
            frame_duration_us = int(round(1_000_000 / self.config.framerate))
            preview_options["controls"] = {"FrameDurationLimits": (frame_duration_us, frame_duration_us)}

        camera_config = self._picam2.create_preview_configuration(**preview_options)
        self._picam2.configure(camera_config)
        self._apply_focus_controls()
        self._picam2.start()

    def stop(self) -> None:
        if self._picam2 is not None:
            self._picam2.stop()
            self._picam2 = None

    def capture_array(self):
        if self._picam2 is None:
            raise RuntimeError("camera has not been started")
        return self._picam2.capture_array()

    def _apply_focus_controls(self) -> None:
        self.set_focus_controls(self.config.focus, self.config.lens_position)

    def set_focus_controls(self, focus: str, lens_position: float) -> None:
        if self._picam2 is None:
            return

        if focus == "none":
            return
        if focus not in {"continuous", "manual"}:
            raise ValueError("focus must be one of: continuous, manual, none")

        try:
            from libcamera import controls
        except ImportError:
            return

        if focus == "continuous":
            self._picam2.set_controls({"AfMode": controls.AfModeEnum.Continuous})
        elif focus == "manual":
            self._picam2.set_controls(
                {
                    "AfMode": controls.AfModeEnum.Manual,
                    "LensPosition": lens_position,
                }
            )
