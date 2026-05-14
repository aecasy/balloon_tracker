"""Image geometry helpers for target tracking."""

from __future__ import annotations

from dataclasses import dataclass
from math import atan2, degrees
from typing import Optional, Tuple

from .calibration import CalibrationData


@dataclass(frozen=True)
class ImageSize:
    width: int
    height: int

    def __post_init__(self) -> None:
        if self.width <= 0 or self.height <= 0:
            raise ValueError("image dimensions must be positive")


@dataclass(frozen=True)
class PixelPoint:
    x: float
    y: float


def image_center(size: ImageSize) -> PixelPoint:
    """Return the optical-center approximation for an image."""
    return PixelPoint((size.width - 1) / 2.0, (size.height - 1) / 2.0)


def pixel_offset(point: PixelPoint, size: ImageSize) -> Tuple[float, float]:
    """Return dx, dy from image center, with positive dy meaning up."""
    center = image_center(size)
    dx = point.x - center.x
    dy = center.y - point.y
    return dx, dy


def pixel_to_bearing_degrees(
    point: PixelPoint,
    size: ImageSize,
    focal_length_px: Tuple[float, float],
) -> Tuple[float, float]:
    """Convert a pixel point to yaw and pitch angles.

    This is a pinhole-camera helper for the future calibrated stage. It assumes
    the optical center is the image center unless calibration supplies a better
    principal point later.
    """
    fx, fy = focal_length_px
    if fx <= 0 or fy <= 0:
        raise ValueError("focal lengths must be positive")

    dx, dy = pixel_offset(point, size)
    yaw = degrees(atan2(dx, fx))
    pitch = degrees(atan2(dy, fy))
    return yaw, pitch


def calibrated_pixel_to_bearing_degrees(
    point: PixelPoint,
    calibration: CalibrationData,
    cv2_module=None,
) -> Tuple[float, float]:
    """Convert a pixel point to yaw/pitch using camera calibration data."""
    normalized_x, normalized_y = normalized_camera_point(point, calibration, cv2_module=cv2_module)
    yaw = degrees(atan2(normalized_x, 1.0))
    pitch = degrees(atan2(-normalized_y, 1.0))
    return yaw, pitch


def normalized_camera_point(
    point: PixelPoint,
    calibration: CalibrationData,
    cv2_module=None,
) -> Tuple[float, float]:
    """Return normalized camera coordinates, with distortion correction when cv2 is available."""
    if cv2_module is False:
        cv2_module = None
        np = None
    elif cv2_module is None:
        try:
            import cv2 as cv2_module
            import numpy as np
        except ImportError:
            cv2_module = None
            np = None
    else:
        import numpy as np

    if cv2_module is not None:
        camera_matrix = np.array(
            [
                [calibration.fx, 0.0, calibration.cx],
                [0.0, calibration.fy, calibration.cy],
                [0.0, 0.0, 1.0],
            ],
            dtype=np.float64,
        )
        distortion = np.array(calibration.distortion_coefficients, dtype=np.float64)
        points = np.array([[[point.x, point.y]]], dtype=np.float64)
        undistorted = cv2_module.undistortPoints(points, camera_matrix, distortion)
        return float(undistorted[0, 0, 0]), float(undistorted[0, 0, 1])

    normalized_x = (point.x - calibration.cx) / calibration.fx
    normalized_y = (point.y - calibration.cy) / calibration.fy
    return normalized_x, normalized_y


def bearing_from_detection(
    point: Optional[PixelPoint],
    calibration: Optional[CalibrationData],
) -> Tuple[Optional[float], Optional[float]]:
    if point is None or calibration is None:
        return None, None
    return calibrated_pixel_to_bearing_degrees(point, calibration)
