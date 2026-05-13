"""Contour-based target tracking and candidate scoring."""

from __future__ import annotations

from dataclasses import dataclass
from time import time
from typing import Dict, List, Optional, Tuple

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
class ScoringConfig:
    min_score: float = 0.55
    color_fill_weight: float = 0.35
    circularity_weight: float = 0.25
    enclosing_fill_weight: float = 0.20
    solidity_weight: float = 0.15
    shading_weight: float = 0.05
    shading_enabled: bool = False
    shading_min_area: float = 400.0

    def __post_init__(self) -> None:
        if not 0.0 <= self.min_score <= 1.0:
            raise ValueError("min_score must be between 0 and 1")
        if self.shading_min_area < 0:
            raise ValueError("shading_min_area must be non-negative")

        weights = [
            self.color_fill_weight,
            self.circularity_weight,
            self.enclosing_fill_weight,
            self.solidity_weight,
            self.shading_weight,
        ]
        if any(weight < 0 for weight in weights):
            raise ValueError("score weights must be non-negative")
        if sum(weights[:-1]) <= 0 and (self.shading_enabled and self.shading_weight <= 0):
            raise ValueError("at least one score weight must be positive")


@dataclass(frozen=True)
class CandidateMetrics:
    area: float
    circularity: float
    enclosing_fill: float
    solidity: float
    color_fill: float
    shading_score: float


@dataclass(frozen=True)
class ScoredCandidate:
    centroid: PixelPoint
    area: float
    circularity: float
    enclosing_fill: float
    solidity: float
    color_fill: float
    shading_score: float
    score: float
    contour: np.ndarray

    def component_scores(self) -> Dict[str, float]:
        return {
            "color_fill": self.color_fill,
            "circularity": self.circularity,
            "enclosing_fill": self.enclosing_fill,
            "solidity": self.solidity,
            "shading": self.shading_score,
        }


@dataclass(frozen=True)
class DetectionResult:
    detected: bool
    centroid: Optional[PixelPoint]
    dx: Optional[int]
    dy: Optional[int]
    area: float
    circularity: float
    timestamp: float
    method: str = "legacy"

    def to_log_line(self, include_components: bool = False) -> str:
        if not self.detected:
            return f"method={self.method} detected=False dx=None dy=None area=0 circularity=0.00"

        return (
            f"method={self.method} detected=True dx={self.dx} dy={self.dy} "
            f"area={int(round(self.area))} circularity={self.circularity:.2f}"
        )


@dataclass(frozen=True)
class ScoredDetectionResult(DetectionResult):
    score: float = 0.0
    enclosing_fill: float = 0.0
    solidity: float = 0.0
    color_fill: float = 0.0
    shading_score: float = 0.0
    candidates: Tuple[ScoredCandidate, ...] = ()

    def to_log_line(self, include_components: bool = False) -> str:
        base = super().to_log_line()
        if not self.detected:
            return f"{base} score=0.00"

        line = f"{base} score={self.score:.2f}"
        if include_components:
            line = (
                f"{line} color_fill={self.color_fill:.2f} "
                f"enclosing_fill={self.enclosing_fill:.2f} solidity={self.solidity:.2f} "
                f"shading={self.shading_score:.2f}"
            )
        return line


class TargetTracker:
    """Tracks either the legacy largest contour or the best scored candidate."""

    def __init__(self, config: TrackerConfig, scoring_config: Optional[ScoringConfig] = None) -> None:
        self.config = config
        self.scoring_config = scoring_config or ScoringConfig()
        self._smoothed_centroid: Optional[PixelPoint] = None

    def update(
        self,
        mask: np.ndarray,
        image_size: ImageSize,
        frame: Optional[np.ndarray] = None,
        method: str = "legacy",
    ) -> DetectionResult:
        if method == "legacy":
            return self.update_legacy(mask, image_size)
        if method == "scored":
            return self.update_scored(mask, image_size, frame)
        raise ValueError("method must be one of: legacy, scored")

    def update_legacy(self, mask: np.ndarray, image_size: ImageSize) -> DetectionResult:
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
                method="legacy",
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
            method="legacy",
        )

    def update_scored(
        self,
        mask: np.ndarray,
        image_size: ImageSize,
        frame: Optional[np.ndarray] = None,
    ) -> ScoredDetectionResult:
        candidates = score_candidates(mask, self.config, self.scoring_config, frame)
        candidate = candidates[0] if candidates else None

        if candidate is None or candidate.score < self.scoring_config.min_score:
            self._smoothed_centroid = None
            return ScoredDetectionResult(
                detected=False,
                centroid=None,
                dx=None,
                dy=None,
                area=0.0,
                circularity=0.0,
                timestamp=time(),
                method="scored",
                candidates=tuple(candidates),
            )

        centroid = self._smooth(candidate.centroid)
        dx, dy = pixel_offset(centroid, image_size)

        return ScoredDetectionResult(
            detected=True,
            centroid=centroid,
            dx=int(round(dx)),
            dy=int(round(dy)),
            area=candidate.area,
            circularity=candidate.circularity,
            timestamp=time(),
            method="scored",
            score=candidate.score,
            enclosing_fill=candidate.enclosing_fill,
            solidity=candidate.solidity,
            color_fill=candidate.color_fill,
            shading_score=candidate.shading_score,
            candidates=tuple(candidates),
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
    candidates = legacy_candidates(mask, min_area, min_circularity)
    if not candidates:
        return None

    candidate = max(candidates, key=lambda item: item[1])
    return candidate


def legacy_candidates(
    mask: np.ndarray,
    min_area: float,
    min_circularity: float,
) -> List[Tuple[PixelPoint, float, float]]:
    contours = find_external_contours(mask)
    candidates: List[Tuple[PixelPoint, float, float]] = []

    for contour in contours:
        area = float(cv2.contourArea(contour))
        if area < min_area:
            continue

        circularity = contour_circularity(contour)
        if circularity < min_circularity:
            continue

        centroid = contour_centroid(contour)
        if centroid is None:
            continue

        candidates.append((centroid, area, circularity))

    return candidates


def score_candidates(
    mask: np.ndarray,
    tracker_config: TrackerConfig,
    scoring_config: ScoringConfig,
    frame: Optional[np.ndarray] = None,
) -> List[ScoredCandidate]:
    candidates: List[ScoredCandidate] = []

    for contour in find_external_contours(mask):
        area = float(cv2.contourArea(contour))
        if area < tracker_config.min_area:
            continue

        centroid = contour_centroid(contour)
        if centroid is None:
            continue

        metrics = candidate_metrics(mask, contour, area, scoring_config, frame)
        score = weighted_candidate_score(metrics, scoring_config)

        candidates.append(
            ScoredCandidate(
                centroid=centroid,
                area=area,
                circularity=metrics.circularity,
                enclosing_fill=metrics.enclosing_fill,
                solidity=metrics.solidity,
                color_fill=metrics.color_fill,
                shading_score=metrics.shading_score,
                score=score,
                contour=contour,
            )
        )

    return sorted(candidates, key=lambda candidate: (candidate.score, candidate.area), reverse=True)


def candidate_metrics(
    mask: np.ndarray,
    contour: np.ndarray,
    area: float,
    scoring_config: ScoringConfig,
    frame: Optional[np.ndarray] = None,
) -> CandidateMetrics:
    return CandidateMetrics(
        area=area,
        circularity=contour_circularity(contour),
        enclosing_fill=enclosing_circle_fill(contour, area),
        solidity=contour_solidity(contour, area),
        color_fill=color_fill_score(mask, contour),
        shading_score=shading_score(frame, contour, area, scoring_config),
    )


def weighted_candidate_score(metrics: CandidateMetrics, config: ScoringConfig) -> float:
    weighted_sum = (
        (metrics.color_fill * config.color_fill_weight)
        + (metrics.circularity * config.circularity_weight)
        + (metrics.enclosing_fill * config.enclosing_fill_weight)
        + (metrics.solidity * config.solidity_weight)
    )
    weight_sum = (
        config.color_fill_weight
        + config.circularity_weight
        + config.enclosing_fill_weight
        + config.solidity_weight
    )

    if config.shading_enabled and config.shading_weight > 0:
        weighted_sum += metrics.shading_score * config.shading_weight
        weight_sum += config.shading_weight

    if weight_sum <= 0:
        return 0.0
    return clamp01(weighted_sum / weight_sum)


def find_external_contours(mask: np.ndarray) -> List[np.ndarray]:
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    return list(contours)


def contour_centroid(contour: np.ndarray) -> Optional[PixelPoint]:
    moments = cv2.moments(contour)
    if moments["m00"] == 0:
        return None

    return PixelPoint(moments["m10"] / moments["m00"], moments["m01"] / moments["m00"])


def contour_circularity(contour: np.ndarray) -> float:
    perimeter = float(cv2.arcLength(contour, True))
    if perimeter <= 0.0:
        return 0.0

    area = float(cv2.contourArea(contour))
    return clamp01(float((4.0 * np.pi * area) / (perimeter * perimeter)))


def enclosing_circle_fill(contour: np.ndarray, area: float) -> float:
    _, radius = cv2.minEnclosingCircle(contour)
    circle_area = float(np.pi * radius * radius)
    if circle_area <= 0.0:
        return 0.0
    return clamp01(area / circle_area)


def contour_solidity(contour: np.ndarray, area: float) -> float:
    hull = cv2.convexHull(contour)
    hull_area = float(cv2.contourArea(hull))
    if hull_area <= 0.0:
        return 0.0
    return clamp01(area / hull_area)


def color_fill_score(mask: np.ndarray, contour: np.ndarray) -> float:
    x, y, w, h = cv2.boundingRect(contour)
    if w <= 0 or h <= 0:
        return 0.0

    roi_mask = mask[y : y + h, x : x + w]
    contour_mask = np.zeros((h, w), dtype=np.uint8)
    shifted_contour = contour - np.array([[[x, y]]])
    cv2.drawContours(contour_mask, [shifted_contour], -1, 255, thickness=-1)

    contour_pixels = contour_mask > 0
    total_pixels = int(np.count_nonzero(contour_pixels))
    if total_pixels <= 0:
        return 0.0

    green_pixels = int(np.count_nonzero((roi_mask > 0) & contour_pixels))
    return clamp01(green_pixels / float(total_pixels))


def shading_score(
    frame: Optional[np.ndarray],
    contour: np.ndarray,
    area: float,
    config: ScoringConfig,
) -> float:
    if not config.shading_enabled or frame is None or area < config.shading_min_area:
        return 0.5

    x, y, w, h = cv2.boundingRect(contour)
    if w <= 2 or h <= 2:
        return 0.5

    roi = frame[y : y + h, x : x + w]
    contour_mask = np.zeros((h, w), dtype=np.uint8)
    shifted_contour = contour - np.array([[[x, y]]])
    cv2.drawContours(contour_mask, [shifted_contour], -1, 255, thickness=-1)

    hsv = cv2.cvtColor(roi, cv2.COLOR_BGR2HSV)
    value_channel = hsv[:, :, 2].astype(np.float32)
    selected_values = value_channel[contour_mask > 0]
    if selected_values.size < 16:
        return 0.5

    blurred = cv2.GaussianBlur(value_channel, (5, 5), 0)
    grad_x = cv2.Sobel(blurred, cv2.CV_32F, 1, 0, ksize=3)
    grad_y = cv2.Sobel(blurred, cv2.CV_32F, 0, 1, ksize=3)
    gradient = cv2.magnitude(grad_x, grad_y)

    mean_gradient = float(np.mean(gradient[contour_mask > 0]))
    smoothness = 1.0 - clamp01(mean_gradient / 64.0)
    contrast = clamp01(float(np.std(selected_values)) / 64.0)
    return clamp01((0.7 * smoothness) + (0.3 * contrast))


def clamp01(value: float) -> float:
    return max(0.0, min(1.0, float(value)))
