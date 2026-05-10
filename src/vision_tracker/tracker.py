"""Contour-based target tracking."""

from __future__ import annotations

from dataclasses import dataclass
from time import time
from typing import List, Optional, Tuple

import cv2
import numpy as np

from .geometry import ImageSize, PixelPoint, pixel_offset


@dataclass(frozen=True)
class TrackerConfig:
    min_area: float = 300.0
    min_circularity: float = 0.55
    smoothing_alpha: float = 0.35

    def __post_init__(self) -> None:
        if self.min_area < 0:
            raise ValueError("min_area must be non-negative")
        if not 0.0 <= self.min_circularity <= 1.0:
            raise ValueError("min_circularity must be between 0 and 1")
        if not 0.0 <= self.smoothing_alpha <= 1.0:
            raise ValueError("smoothing_alpha must be between 0 and 1")


@dataclass(frozen=True)
class DetectionResult:
    detected: bool
    centroid: Optional[PixelPoint]
    dx: Optional[int]
    dy: Optional[int]
    area: float
    circularity: float
    timestamp: float

    def to_log_line(self) -> str:
        if not self.detected:
            return "detected=False dx=None dy=None area=0 circularity=0.00"

        return (
            f"detected=True dx={self.dx} dy={self.dy} "
            f"area={int(round(self.area))} circularity={self.circularity:.2f}"
        )


class TargetTracker:
    """Tracks the largest contour that passes area and circularity gates."""

    def __init__(self, config: TrackerConfig) -> None:
        self.config = config
        self._smoothed_centroid: Optional[PixelPoint] = None

    def update(self, mask: np.ndarray, image_size: ImageSize) -> DetectionResult:
        candidate = find_best_contour(
            mask,
            min_area=self.config.min_area,
            min_circularity=self.config.min_circularity,
        )

        if candidate is None:
            self._smoothed_centroid = None
            return DetectionResult(
                detected=False,
                centroid=None,
                dx=None,
                dy=None,
                area=0.0,
                circularity=0.0,
                timestamp=time(),
            )

        centroid, area, circularity = candidate
        centroid = self._smooth(centroid)
        dx, dy = pixel_offset(centroid, image_size)

        return DetectionResult(
            detected=True,
            centroid=centroid,
            dx=int(round(dx)),
            dy=int(round(dy)),
            area=area,
            circularity=circularity,
            timestamp=time(),
        )

    def _smooth(self, centroid: PixelPoint) -> PixelPoint:
        alpha = self.config.smoothing_alpha
        if self._smoothed_centroid is None or alpha >= 1.0:
            self._smoothed_centroid = centroid
            return centroid

        previous = self._smoothed_centroid
        smoothed = PixelPoint(
            x=(alpha * centroid.x) + ((1.0 - alpha) * previous.x),
            y=(alpha * centroid.y) + ((1.0 - alpha) * previous.y),
        )
        self._smoothed_centroid = smoothed
        return smoothed


def find_best_contour(
    mask: np.ndarray,
    min_area: float,
    min_circularity: float,
) -> Optional[Tuple[PixelPoint, float, float]]:
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    candidates: List[Tuple[PixelPoint, float, float]] = []

    for contour in contours:
        area = float(cv2.contourArea(contour))
        if area < min_area:
            continue

        circularity = contour_circularity(contour)
        if circularity < min_circularity:
            continue

        moments = cv2.moments(contour)
        if moments["m00"] == 0:
            continue

        cx = moments["m10"] / moments["m00"]
        cy = moments["m01"] / moments["m00"]
        candidates.append((PixelPoint(cx, cy), area, circularity))

    if not candidates:
        return None

    return max(candidates, key=lambda item: item[1])


def contour_circularity(contour: np.ndarray) -> float:
    perimeter = float(cv2.arcLength(contour, True))
    if perimeter <= 0.0:
        return 0.0

    area = float(cv2.contourArea(contour))
    return float((4.0 * np.pi * area) / (perimeter * perimeter))
