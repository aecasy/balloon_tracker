#!/usr/bin/env python3
"""Compare legacy and scored target selection on a live camera feed."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path
from typing import Iterable, Tuple

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

import cv2

from vision_tracker.camera import CameraConfig, PiCamera
from vision_tracker.color_detector import create_hsv_mask
from vision_tracker.config import default_config_path, load_app_config, with_overrides
from vision_tracker.geometry import ImageSize
from vision_tracker.tracker import DetectionResult, ScoredDetectionResult, TargetTracker


def main() -> int:
    args = parse_args()
    config_path = args.config.resolve()
    config = load_app_config(config_path)
    config = with_overrides(
        config,
        width=args.width,
        height=args.height,
        focus=args.focus,
        lens_position=args.lens_position,
    )

    camera_config = CameraConfig(
        width=config.camera.width,
        height=config.camera.height,
        pixel_format=config.camera.pixel_format,
        focus=config.camera.focus,
        lens_position=config.camera.lens_position,
    )
    image_size = ImageSize(width=config.camera.width, height=config.camera.height)
    legacy_tracker = TargetTracker(config.tracker, config.scoring)
    scored_tracker = TargetTracker(config.tracker, config.scoring)

    print(f"loaded_config={config_path}", flush=True)
    print("legacy is yellow, scored is magenta; press q to quit", flush=True)

    try:
        with PiCamera(camera_config) as camera:
            while True:
                frame = camera.capture_array()
                mask = create_hsv_mask(
                    frame,
                    config.hsv,
                    open_iterations=config.morphology.open_iterations,
                    close_iterations=config.morphology.close_iterations,
                    kernel_size=config.morphology.kernel_size,
                )

                legacy_result = legacy_tracker.update_legacy(mask, image_size)
                scored_result = scored_tracker.update_scored(mask, image_size, frame)

                display_frame = frame.copy()
                draw_center(display_frame)
                draw_result(display_frame, legacy_result, (0, 255, 255), "legacy")
                draw_result(display_frame, scored_result, (255, 0, 255), "scored")
                draw_candidate_table(display_frame, scored_result)

                print(
                    f"{legacy_result.to_log_line()} | {scored_result.to_log_line(include_components=True)}",
                    flush=True,
                )

                cv2.imshow("comparison", display_frame)
                cv2.imshow("mask", mask)
                if cv2.waitKey(1) & 0xFF == ord("q"):
                    break
    except KeyboardInterrupt:
        pass
    finally:
        cv2.destroyAllWindows()

    return 0


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Compare legacy and scored target selection live.")
    parser.add_argument(
        "--config",
        type=Path,
        default=default_config_path(PROJECT_ROOT),
        help="tracker JSON config file",
    )
    parser.add_argument("--width", type=int, default=None, help="temporary camera image width override")
    parser.add_argument("--height", type=int, default=None, help="temporary camera image height override")
    parser.add_argument("--focus", choices=["continuous", "manual", "none"], default=None, help="temporary focus mode override")
    parser.add_argument("--lens-position", type=float, default=None, help="temporary manual focus lens position override")
    return parser.parse_args()


def draw_center(frame) -> None:
    height, width = frame.shape[:2]
    cv2.drawMarker(
        frame,
        (width // 2, height // 2),
        (255, 255, 255),
        markerType=cv2.MARKER_CROSS,
        markerSize=20,
        thickness=1,
    )


def draw_result(frame, result: DetectionResult, color: Tuple[int, int, int], label: str) -> None:
    if not result.detected or result.centroid is None:
        return

    target = (int(round(result.centroid.x)), int(round(result.centroid.y)))
    cv2.circle(frame, target, 12, color, 2)
    cv2.putText(frame, label, (target[0] + 12, target[1] - 8), cv2.FONT_HERSHEY_SIMPLEX, 0.5, color, 1, cv2.LINE_AA)


def draw_candidate_table(frame, result: ScoredDetectionResult) -> None:
    rows = [
        "rank area rel fit circ fill sol color shade score",
    ]
    for index, candidate in enumerate(result.candidates[:5], start=1):
        rows.append(
            f"{index:>2} {candidate.area:>5.0f} {format_metric(candidate.relative_area)} "
            f"{format_metric(candidate.circle_fit)} {format_metric(candidate.circularity)} "
            f"{format_metric(candidate.enclosing_fill)} {format_metric(candidate.solidity)} "
            f"{format_metric(candidate.color_fill)} {format_metric(candidate.shading_score)} {candidate.score:.2f}"
        )

    draw_text_panel(frame, rows, origin=(10, 28))


def draw_text_panel(frame, lines: Iterable[str], origin: Tuple[int, int]) -> None:
    x, y = origin
    line_list = list(lines)
    width = 540
    height = 24 + (len(line_list) * 20)
    overlay = frame.copy()
    cv2.rectangle(overlay, (x - 6, y - 22), (x + width, y - 22 + height), (0, 0, 0), -1)
    cv2.addWeighted(overlay, 0.45, frame, 0.55, 0, frame)

    for line in line_list:
        cv2.putText(frame, line, (x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.45, (230, 235, 240), 1, cv2.LINE_AA)
        y += 20


def format_metric(value) -> str:
    if value is None:
        return "off"
    return f"{value:.2f}"


if __name__ == "__main__":
    raise SystemExit(main())
