"""Picamera2 setup helpers."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Optional


@dataclass(frozen=True)
class CameraConfig:
    width: int = 640
    height: int = 480
    raw_width: Optional[int] = None
    raw_height: Optional[int] = None
    pixel_format: str = "RGB888"
    focus: str = "continuous"
    lens_position: float = 2.0
    awb_mode: str = "auto"
    exposure_time: int = 0
    analogue_gain: float = 0.0
    min_framerate: float = 0.0

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

        camera_config = self._picam2.create_preview_configuration(**preview_options)
        self._picam2.configure(camera_config)
        self._apply_camera_controls()
        self._picam2.start()

    def stop(self) -> None:
        if self._picam2 is not None:
            self._picam2.stop()
            self._picam2 = None

    def capture_array(self):
        if self._picam2 is None:
            raise RuntimeError("camera has not been started")
        return self._picam2.capture_array()

    def _apply_camera_controls(self) -> None:
        self.set_camera_controls(
            self.config.focus,
            self.config.lens_position,
            self.config.awb_mode,
            self.config.exposure_time,
            self.config.analogue_gain,
            self.config.min_framerate,
        )

    def set_camera_controls(
        self,
        focus: str,
        lens_position: float,
        awb_mode: str = "auto",
        exposure_time: int = 0,
        analogue_gain: float = 0.0,
        min_framerate: float = 0.0,
    ) -> None:
        if self._picam2 is None:
            return

        try:
            from libcamera import controls
        except ImportError:
            return

        ctrls = {}

        if focus == "continuous":
            ctrls["AfMode"] = controls.AfModeEnum.Continuous
        elif focus == "manual":
            ctrls["AfMode"] = controls.AfModeEnum.Manual
            ctrls["LensPosition"] = lens_position

        if hasattr(controls, "AwbModeEnum"):
            awb_map = {
                "auto": controls.AwbModeEnum.Auto,
                "incandescent": controls.AwbModeEnum.Incandescent,
                "tungsten": controls.AwbModeEnum.Tungsten,
                "fluorescent": controls.AwbModeEnum.Fluorescent,
                "indoor": controls.AwbModeEnum.Indoor,
                "daylight": controls.AwbModeEnum.Daylight,
                "cloudy": controls.AwbModeEnum.Cloudy,
                "custom": controls.AwbModeEnum.Custom,
            }
            if awb_mode in awb_map:
                ctrls["AwbMode"] = awb_map[awb_mode]

        if exposure_time > 0:
            ctrls["AeEnable"] = False
            ctrls["ExposureTime"] = exposure_time
        else:
            ctrls["AeEnable"] = True

        if analogue_gain > 0.0:
            ctrls["AnalogueGain"] = analogue_gain

        if min_framerate > 0.0:
            max_duration = int(1_000_000 / min_framerate)
            ctrls["FrameDurationLimits"] = (100, max_duration)

        if ctrls:
            self._picam2.set_controls(ctrls)
