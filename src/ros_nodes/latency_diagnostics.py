"""Latency diagnostics helpers for ROS bridge timing."""

from __future__ import annotations

from collections import deque
import json
from math import ceil
from typing import Any, Deque, Dict, Optional


TRUTHY_VALUES = {"1", "true", "yes", "on", "enabled"}


def is_enabled(value: Optional[str]) -> bool:
    return str(value or "").strip().lower() in TRUTHY_VALUES


def _to_float(value: Any) -> Optional[float]:
    if value is None:
        return None
    try:
        return float(value)
    except (TypeError, ValueError):
        return None


def _elapsed_ms(start: Optional[float], end: Optional[float]) -> Optional[float]:
    if start is None or end is None:
        return None
    return (end - start) * 1000.0


def build_latency_payload(
    frame: Dict[str, Any],
    sequence: int,
    docker_receive_time: float,
    ros_publish_time: float,
) -> Dict[str, Any]:
    tracker_timestamp = _to_float(frame.get("timestamp"))
    detected = bool(frame.get("detected", False))

    return {
        "sequence": sequence,
        "detected": detected,
        "tracker_timestamp": tracker_timestamp,
        "docker_receive_time": docker_receive_time,
        "ros_publish_time": ros_publish_time,
        "tracker_to_docker_ms": _elapsed_ms(tracker_timestamp, docker_receive_time),
        "docker_to_publish_ms": _elapsed_ms(docker_receive_time, ros_publish_time),
        "tracker_to_publish_ms": _elapsed_ms(tracker_timestamp, ros_publish_time),
    }


def format_latency_payload(payload: Dict[str, Any]) -> str:
    return json.dumps(payload, separators=(",", ":"))


class RollingLatencyStats:
    def __init__(self, window_size: int = 200):
        self.samples: Deque[Dict[str, Any]] = deque(maxlen=max(1, int(window_size)))

    def add(self, payload: Dict[str, Any]) -> None:
        self.samples.append(payload)

    def summary(self, key: str) -> Optional[Dict[str, float]]:
        values = sorted(
            float(sample[key])
            for sample in self.samples
            if sample.get(key) is not None
        )
        if not values:
            return None

        p95_index = max(0, ceil(len(values) * 0.95) - 1)
        return {
            "count": len(values),
            "min": values[0],
            "avg": sum(values) / len(values),
            "max": values[-1],
            "p95": values[p95_index],
        }
