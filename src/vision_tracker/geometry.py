"""Image geometry helpers for target tracking."""

from __future__ import annotations

from dataclasses import dataclass
from math import atan2, degrees
from typing import Tuple


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
