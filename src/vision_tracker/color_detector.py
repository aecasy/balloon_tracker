"""HSV color segmentation utilities."""

from __future__ import annotations

from dataclasses import dataclass
from typing import Tuple

import cv2
import numpy as np


@dataclass(frozen=True)
class HsvRange:
    lower: Tuple[int, int, int] = (68, 180, 20)
    upper: Tuple[int, int, int] = (88, 255, 255)

    def __post_init__(self) -> None:
        _validate_hsv_triplet(self.lower, "lower")
        _validate_hsv_triplet(self.upper, "upper")

    @property
    def lower_array(self) -> np.ndarray:
        return np.array(self.lower, dtype=np.uint8)

    @property
    def upper_array(self) -> np.ndarray:
        return np.array(self.upper, dtype=np.uint8)


def create_hsv_mask(
    frame: np.ndarray,
    hsv_range: HsvRange,
    open_iterations: int = 1,
    close_iterations: int = 2,
    kernel_size: int = 5,
) -> np.ndarray:
    """Create a cleaned binary mask for pixels inside the HSV range."""
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(hsv, hsv_range.lower_array, hsv_range.upper_array)

    if kernel_size > 0:
        kernel = np.ones((kernel_size, kernel_size), dtype=np.uint8)
        if open_iterations > 0:
            mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel, iterations=open_iterations)
        if close_iterations > 0:
            mask = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel, iterations=close_iterations)

    return mask


def parse_hsv_triplet(value: str) -> Tuple[int, int, int]:
    """Parse H,S,V command-line input such as '68,180,20'."""
    parts = value.split(",")
    if len(parts) != 3:
        raise ValueError("HSV value must have three comma-separated integers")

    try:
        triplet = tuple(int(part.strip()) for part in parts)
    except ValueError as exc:
        raise ValueError("HSV value must contain only integers") from exc

    _validate_hsv_triplet(triplet, "HSV")
    return triplet


def _validate_hsv_triplet(value: Tuple[int, int, int], label: str) -> None:
    if len(value) != 3:
        raise ValueError(f"{label} HSV value must contain three values")

    h, s, v = value
    if not 0 <= h <= 179:
        raise ValueError(f"{label} hue must be between 0 and 179")
    if not 0 <= s <= 255:
        raise ValueError(f"{label} saturation must be between 0 and 255")
    if not 0 <= v <= 255:
        raise ValueError(f"{label} value must be between 0 and 255")
