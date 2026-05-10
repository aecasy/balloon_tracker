"""JSON configuration for tracker tuning and runtime."""

from __future__ import annotations

import json
from dataclasses import asdict, dataclass, field
from pathlib import Path
from typing import Any, Dict, Tuple

from .camera import CameraConfig
from .color_detector import HsvRange
from .tracker import TrackerConfig


@dataclass(frozen=True)
class MorphologyConfig:
    kernel_size: int = 5
    open_iterations: int = 1
    close_iterations: int = 2

    def __post_init__(self) -> None:
        if self.kernel_size < 0:
            raise ValueError("kernel_size must be non-negative")
        if self.open_iterations < 0:
            raise ValueError("open_iterations must be non-negative")
        if self.close_iterations < 0:
            raise ValueError("close_iterations must be non-negative")


@dataclass(frozen=True)
class AppConfig:
    camera: CameraConfig = field(default_factory=CameraConfig)
    hsv: HsvRange = field(default_factory=HsvRange)
    morphology: MorphologyConfig = field(default_factory=MorphologyConfig)
    tracker: TrackerConfig = field(default_factory=TrackerConfig)


def default_config_path(project_root: Path) -> Path:
    return project_root / "config" / "green_tracker.json"


def load_app_config(path: Path) -> AppConfig:
    if not path.exists():
        return AppConfig()

    with path.open("r", encoding="utf-8") as config_file:
        data = json.load(config_file)

    return app_config_from_dict(data)


def save_app_config(config: AppConfig, path: Path) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="\n") as config_file:
        json.dump(app_config_to_dict(config), config_file, indent=2)
        config_file.write("\n")


def app_config_to_dict(config: AppConfig) -> Dict[str, Any]:
    return asdict(config)


def app_config_from_dict(data: Dict[str, Any]) -> AppConfig:
    camera_data = data.get("camera", {})
    hsv_data = data.get("hsv", {})
    morphology_data = data.get("morphology", {})
    tracker_data = data.get("tracker", {})

    return AppConfig(
        camera=CameraConfig(
            width=int(camera_data.get("width", 640)),
            height=int(camera_data.get("height", 480)),
            pixel_format=str(camera_data.get("pixel_format", "RGB888")),
            focus=str(camera_data.get("focus", "continuous")),
            lens_position=float(camera_data.get("lens_position", 2.0)),
        ),
        hsv=HsvRange(
            lower=_hsv_tuple(hsv_data.get("lower", (68, 180, 20))),
            upper=_hsv_tuple(hsv_data.get("upper", (88, 255, 255))),
        ),
        morphology=MorphologyConfig(
            kernel_size=int(morphology_data.get("kernel_size", 5)),
            open_iterations=int(morphology_data.get("open_iterations", 1)),
            close_iterations=int(morphology_data.get("close_iterations", 2)),
        ),
        tracker=TrackerConfig(
            min_area=float(tracker_data.get("min_area", 300.0)),
            min_circularity=float(tracker_data.get("min_circularity", 0.55)),
            smoothing_alpha=float(tracker_data.get("smoothing_alpha", 0.35)),
        ),
    )


def with_overrides(config: AppConfig, **overrides: Any) -> AppConfig:
    camera = CameraConfig(
        width=_value_or(config.camera.width, overrides.get("width")),
        height=_value_or(config.camera.height, overrides.get("height")),
        pixel_format=config.camera.pixel_format,
        focus=_value_or(config.camera.focus, overrides.get("focus")),
        lens_position=_value_or(config.camera.lens_position, overrides.get("lens_position")),
    )
    hsv = HsvRange(
        lower=_value_or(config.hsv.lower, overrides.get("lower_hsv")),
        upper=_value_or(config.hsv.upper, overrides.get("upper_hsv")),
    )
    morphology = MorphologyConfig(
        kernel_size=_value_or(config.morphology.kernel_size, overrides.get("kernel_size")),
        open_iterations=_value_or(config.morphology.open_iterations, overrides.get("open_iterations")),
        close_iterations=_value_or(config.morphology.close_iterations, overrides.get("close_iterations")),
    )
    tracker = TrackerConfig(
        min_area=_value_or(config.tracker.min_area, overrides.get("min_area")),
        min_circularity=_value_or(config.tracker.min_circularity, overrides.get("min_circularity")),
        smoothing_alpha=_value_or(config.tracker.smoothing_alpha, overrides.get("smoothing_alpha")),
    )
    return AppConfig(camera=camera, hsv=hsv, morphology=morphology, tracker=tracker)


def _hsv_tuple(value: Any) -> Tuple[int, int, int]:
    if not isinstance(value, (list, tuple)) or len(value) != 3:
        raise ValueError("HSV config values must be lists of three integers")
    return (int(value[0]), int(value[1]), int(value[2]))


def _value_or(current: Any, override: Any) -> Any:
    if override is None:
        return current
    return override
