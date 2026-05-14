"""Camera calibration file helpers."""

from __future__ import annotations

import json
from dataclasses import asdict, dataclass
from pathlib import Path
from typing import List, Optional


@dataclass(frozen=True)
class CalibrationData:
    image_width: int
    image_height: int
    fx: float
    fy: float
    cx: float
    cy: float
    distortion_coefficients: List[float]
    reprojection_error: float
    pattern_cols: int
    pattern_rows: int
    square_size_mm: float
    sample_count: int
    created_at: str

    def __post_init__(self) -> None:
        if self.image_width <= 0 or self.image_height <= 0:
            raise ValueError("calibration image dimensions must be positive")
        if self.fx <= 0 or self.fy <= 0:
            raise ValueError("calibration focal lengths must be positive")
        if self.pattern_cols <= 0 or self.pattern_rows <= 0:
            raise ValueError("checkerboard dimensions must be positive")
        if self.square_size_mm <= 0:
            raise ValueError("checkerboard square size must be positive")
        if self.sample_count <= 0:
            raise ValueError("calibration sample count must be positive")


def default_calibration_path(project_root: Path) -> Path:
    return project_root / "config" / "camera_calibration.json"


def load_calibration(path: Path) -> CalibrationData:
    with path.open("r", encoding="utf-8") as calibration_file:
        data = json.load(calibration_file)
    return calibration_from_dict(data)


def load_calibration_optional(path: Path) -> Optional[CalibrationData]:
    if not path.exists():
        return None
    return load_calibration(path)


def save_calibration(calibration: CalibrationData, path: Path) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="\n") as calibration_file:
        json.dump(asdict(calibration), calibration_file, indent=2)
        calibration_file.write("\n")


def calibration_from_dict(data) -> CalibrationData:
    return CalibrationData(
        image_width=int(data["image_width"]),
        image_height=int(data["image_height"]),
        fx=float(data["fx"]),
        fy=float(data["fy"]),
        cx=float(data["cx"]),
        cy=float(data["cy"]),
        distortion_coefficients=[float(value) for value in data.get("distortion_coefficients", [])],
        reprojection_error=float(data.get("reprojection_error", 0.0)),
        pattern_cols=int(data["pattern_cols"]),
        pattern_rows=int(data["pattern_rows"]),
        square_size_mm=float(data["square_size_mm"]),
        sample_count=int(data["sample_count"]),
        created_at=str(data["created_at"]),
    )
