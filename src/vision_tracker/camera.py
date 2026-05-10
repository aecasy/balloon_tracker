"""Picamera2 setup helpers."""

from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class CameraConfig:
    width: int = 640
    height: int = 480
    pixel_format: str = "RGB888"
    focus: str = "continuous"
    lens_position: float = 2.0

    def __post_init__(self) -> None:
        if self.width <= 0 or self.height <= 0:
            raise ValueError("camera dimensions must be positive")
        if self.focus not in {"continuous", "manual", "none"}:
            raise ValueError("focus must be one of: continuous, manual, none")


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
        camera_config = self._picam2.create_preview_configuration(
            main={"size": (self.config.width, self.config.height), "format": self.config.pixel_format}
        )
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
