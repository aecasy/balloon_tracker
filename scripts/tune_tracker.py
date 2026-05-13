#!/usr/bin/env python3
"""Tune tracker parameters with grouped OpenCV sliders and hover help."""

from __future__ import annotations

import argparse
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Tuple

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

import cv2
import numpy as np

from vision_tracker.camera import CameraConfig, PiCamera
from vision_tracker.color_detector import HsvRange, create_hsv_mask
from vision_tracker.config import (
    AppConfig,
    MorphologyConfig,
    default_config_path,
    load_app_config,
    save_app_config,
    with_overrides,
)
from vision_tracker.geometry import ImageSize
from vision_tracker.tracker import TargetTracker, TrackerConfig

CONTROLS_WINDOW = "tracker controls"
CAMERA_WINDOW = "camera"
MASK_WINDOW = "mask"
FOCUS_MODES = ("none", "continuous", "manual")
PANEL_WIDTH = 760
PANEL_HEIGHT = 920


@dataclass(frozen=True)
class ControlSpec:
    key: str
    label: str
    group: str
    minimum: int
    maximum: int
    tooltip: str
    value_suffix: str = ""
    choices: Tuple[str, ...] = ()


@dataclass
class ControlRow:
    spec: ControlSpec
    label_rect: Tuple[int, int, int, int]
    track_rect: Tuple[int, int, int, int]


class ControlPanel:
    def __init__(self, config: AppConfig, max_area: int) -> None:
        self.max_area = max_area
        self.specs = build_control_specs(max_area)
        self.values = initial_control_values(config)
        self.rows: List[ControlRow] = []
        self.hover_key: Optional[str] = None
        self.drag_key: Optional[str] = None

        cv2.namedWindow(CONTROLS_WINDOW)
        cv2.resizeWindow(CONTROLS_WINDOW, PANEL_WIDTH, PANEL_HEIGHT)
        cv2.setMouseCallback(CONTROLS_WINDOW, self.handle_mouse)

    def read_config(self, base_config: AppConfig) -> AppConfig:
        lower = (
            self.value("lower_h"),
            self.value("lower_s"),
            self.value("lower_v"),
        )
        upper = (
            self.value("upper_h"),
            self.value("upper_s"),
            self.value("upper_v"),
        )

        kernel_size = self.value("kernel")
        if kernel_size > 0 and kernel_size % 2 == 0:
            kernel_size += 1

        focus_index = int(clamp(self.value("focus_mode"), 0, len(FOCUS_MODES) - 1))

        return AppConfig(
            camera=CameraConfig(
                width=base_config.camera.width,
                height=base_config.camera.height,
                pixel_format=base_config.camera.pixel_format,
                focus=FOCUS_MODES[focus_index],
                lens_position=self.value("lens_x100") / 100.0,
            ),
            hsv=HsvRange(lower=lower, upper=upper),
            morphology=MorphologyConfig(
                kernel_size=kernel_size,
                open_iterations=self.value("open_iters"),
                close_iterations=self.value("close_iters"),
            ),
            tracker=TrackerConfig(
                min_area=float(clamp(self.value("min_area"), 0, self.max_area)),
                min_circularity=self.value("circularity_pct") / 100.0,
                smoothing_alpha=self.value("smoothing_pct") / 100.0,
            ),
        )

    def draw(self, config: AppConfig) -> None:
        canvas = np.full((PANEL_HEIGHT, PANEL_WIDTH, 3), (34, 38, 42), dtype=np.uint8)
        self.rows = []

        cv2.putText(canvas, "Tracker tuning", (24, 34), cv2.FONT_HERSHEY_SIMPLEX, 0.78, (240, 240, 240), 2)
        cv2.putText(canvas, "Press s to save, q to quit", (24, 62), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (190, 195, 200), 1)

        y = 98
        current_group = ""
        for spec in self.specs:
            if spec.group != current_group:
                current_group = spec.group
                y += 12
                draw_group_header(canvas, current_group, y)
                y += 32

            row = self.draw_slider(canvas, spec, y)
            self.rows.append(row)
            y += 36

        self.draw_help(canvas, config)
        cv2.imshow(CONTROLS_WINDOW, canvas)

    def draw_slider(self, canvas: np.ndarray, spec: ControlSpec, y: int) -> ControlRow:
        label_x = 28
        value_x = 196
        track_x = 280
        track_y = y - 6
        track_w = 380
        track_h = 12
        knob_radius = 8

        hovered = self.hover_key == spec.key
        text_color = (255, 255, 255) if hovered else (210, 215, 220)
        track_color = (90, 100, 108)
        fill_color = (69, 190, 120) if hovered else (60, 155, 105)

        cv2.putText(canvas, spec.label, (label_x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.48, text_color, 1)
        cv2.putText(canvas, self.format_value(spec), (value_x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.48, text_color, 1)

        cv2.rectangle(canvas, (track_x, track_y), (track_x + track_w, track_y + track_h), track_color, -1)

        value = self.value(spec.key)
        ratio = 0.0 if spec.maximum == spec.minimum else (value - spec.minimum) / float(spec.maximum - spec.minimum)
        ratio = clamp_float(ratio, 0.0, 1.0)
        knob_x = int(track_x + ratio * track_w)
        cv2.rectangle(canvas, (track_x, track_y), (knob_x, track_y + track_h), fill_color, -1)
        cv2.circle(canvas, (knob_x, track_y + track_h // 2), knob_radius, (235, 245, 238), -1)

        label_rect = (label_x - 4, y - 22, track_x + track_w + 24, y + 12)
        track_rect = (track_x, track_y - 8, track_w, track_h + 16)
        return ControlRow(spec=spec, label_rect=label_rect, track_rect=track_rect)

    def draw_help(self, canvas: np.ndarray, config: AppConfig) -> None:
        x = 24
        y = 790
        w = 712
        h = 116
        cv2.rectangle(canvas, (x, y), (x + w, y + h), (48, 54, 60), -1)
        cv2.rectangle(canvas, (x, y), (x + w, y + h), (82, 92, 100), 1)

        spec = self.find_spec(self.hover_key)
        if spec is None:
            title = "Hover any control for help"
            body = "Start with HSV. Then adjust min area and circularity. Morphology and focus are advanced cleanup controls."
        else:
            title = spec.label
            body = spec.tooltip

        cv2.putText(canvas, title, (x + 14, y + 28), cv2.FONT_HERSHEY_SIMPLEX, 0.58, (245, 245, 245), 1)
        draw_wrapped_text(canvas, body, x + 14, y + 56, 96, (205, 212, 218))

        summary = (
            f"Saved shape: HSV {config.hsv.lower}-{config.hsv.upper}, "
            f"area {config.tracker.min_area:.0f}, circ {config.tracker.min_circularity:.2f}"
        )
        cv2.putText(canvas, summary, (x + 14, y + 102), cv2.FONT_HERSHEY_SIMPLEX, 0.44, (150, 210, 170), 1)

    def handle_mouse(self, event: int, x: int, y: int, flags: int, param) -> None:
        if event == cv2.EVENT_MOUSEMOVE:
            self.hover_key = self.key_at(x, y)
            if self.drag_key is not None:
                self.update_value_from_mouse(self.drag_key, x)
        elif event == cv2.EVENT_LBUTTONDOWN:
            self.drag_key = self.key_at(x, y)
            if self.drag_key is not None:
                self.update_value_from_mouse(self.drag_key, x)
        elif event == cv2.EVENT_LBUTTONUP:
            self.drag_key = None

    def key_at(self, x: int, y: int) -> Optional[str]:
        for row in self.rows:
            if point_in_rect(x, y, row.label_rect):
                return row.spec.key
        return None

    def update_value_from_mouse(self, key: str, x: int) -> None:
        row = self.find_row(key)
        if row is None:
            return

        spec = row.spec
        track_x, _, track_w, _ = row.track_rect
        ratio = clamp_float((x - track_x) / float(track_w), 0.0, 1.0)
        value = int(round(spec.minimum + ratio * (spec.maximum - spec.minimum)))
        self.values[key] = int(clamp(value, spec.minimum, spec.maximum))

    def format_value(self, spec: ControlSpec) -> str:
        value = self.value(spec.key)
        if spec.choices:
            index = int(clamp(value, 0, len(spec.choices) - 1))
            return spec.choices[index]
        if spec.key == "kernel":
            effective = value
            if effective > 0 and effective % 2 == 0:
                effective += 1
            return f"{value} -> {effective}"
        if spec.key in {"circularity_pct", "smoothing_pct"}:
            return f"{value / 100.0:.2f}"
        if spec.key == "lens_x100":
            return f"{value / 100.0:.2f}"
        return f"{value}{spec.value_suffix}"

    def value(self, key: str) -> int:
        return self.values[key]

    def find_row(self, key: str) -> Optional[ControlRow]:
        for row in self.rows:
            if row.spec.key == key:
                return row
        return None

    def find_spec(self, key: Optional[str]) -> Optional[ControlSpec]:
        if key is None:
            return None
        for spec in self.specs:
            if spec.key == key:
                return spec
        return None


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

    panel = ControlPanel(config, args.max_area)
    tracker = TargetTracker(config.tracker)
    image_size = ImageSize(config.camera.width, config.camera.height)

    print(f"loaded_config={config_path}", flush=True)
    print("press s to save, q to quit", flush=True)

    last_focus = None
    last_lens_position = None

    try:
        with PiCamera(config.camera) as camera:
            while True:
                live_config = panel.read_config(config)
                tracker.config = live_config.tracker

                if (
                    live_config.camera.focus != last_focus
                    or live_config.camera.lens_position != last_lens_position
                ):
                    camera.set_focus_controls(live_config.camera.focus, live_config.camera.lens_position)
                    last_focus = live_config.camera.focus
                    last_lens_position = live_config.camera.lens_position

                frame = camera.capture_array()
                mask = create_hsv_mask(
                    frame,
                    live_config.hsv,
                    open_iterations=live_config.morphology.open_iterations,
                    close_iterations=live_config.morphology.close_iterations,
                    kernel_size=live_config.morphology.kernel_size,
                )
                result = tracker.update(mask, image_size)

                display_frame = frame.copy()
                draw_detection(display_frame, result)
                draw_tuning_status(display_frame, live_config, result)

                panel.draw(live_config)
                cv2.imshow(CAMERA_WINDOW, display_frame)
                cv2.imshow(MASK_WINDOW, mask)

                key = cv2.waitKey(1) & 0xFF
                if key == ord("s"):
                    save_app_config(live_config, config_path)
                    print(f"saved_config={config_path}", flush=True)
                elif key == ord("q"):
                    break
    except KeyboardInterrupt:
        pass
    finally:
        cv2.destroyAllWindows()

    return 0


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Tune green tracker parameters with live grouped sliders.")
    parser.add_argument(
        "--config",
        type=Path,
        default=default_config_path(PROJECT_ROOT),
        help="tracker JSON config file to load and save",
    )
    parser.add_argument("--width", type=int, default=None, help="temporary camera width override")
    parser.add_argument("--height", type=int, default=None, help="temporary camera height override")
    parser.add_argument("--focus", choices=FOCUS_MODES, default=None, help="temporary focus mode override")
    parser.add_argument("--lens-position", type=float, default=None, help="temporary manual lens position override")
    parser.add_argument("--max-area", type=int, default=50000, help="maximum value for the min-area slider")
    return parser.parse_args()


def build_control_specs(max_area: int) -> List[ControlSpec]:
    return [
        ControlSpec(
            "lower_h",
            "Lower H",
            "Target color - start here",
            0,
            179,
            "Minimum hue accepted as target. Raise it if non-green colors enter the mask.",
        ),
        ControlSpec(
            "upper_h",
            "Upper H",
            "Target color - start here",
            0,
            179,
            "Maximum hue accepted as target. Lower it if nearby colors are being accepted.",
        ),
        ControlSpec(
            "lower_s",
            "Lower S",
            "Target color - start here",
            0,
            255,
            "Minimum saturation. Raise it to reject pale gray, white, and weakly colored objects.",
        ),
        ControlSpec(
            "upper_s",
            "Upper S",
            "Target color - start here",
            0,
            255,
            "Maximum saturation. Usually leave this at 255 unless the target is over-saturated by lighting.",
        ),
        ControlSpec(
            "lower_v",
            "Lower V",
            "Target color - start here",
            0,
            255,
            "Minimum brightness. Raise it to reject dark noise; lower it if the ball is detected poorly in shade.",
        ),
        ControlSpec(
            "upper_v",
            "Upper V",
            "Target color - start here",
            0,
            255,
            "Maximum brightness. Usually leave this at 255; lower only if bright reflections are a problem.",
        ),
        ControlSpec(
            "min_area",
            "Min area",
            "Detection quality",
            0,
            max_area,
            "Smallest contour allowed. Raise it to reject specks; lower it if the ball is far away.",
            " px",
        ),
        ControlSpec(
            "circularity_pct",
            "Circularity",
            "Detection quality",
            0,
            100,
            "How round the contour must be. Raise it to reject blobs; lower it if the ball edge is noisy.",
        ),
        ControlSpec(
            "smoothing_pct",
            "Smoothing",
            "Detection quality",
            0,
            100,
            "Centroid smoothing alpha. Higher follows motion faster; lower gives steadier but laggier output.",
        ),
        ControlSpec(
            "kernel",
            "Kernel",
            "Mask cleanup - advanced",
            0,
            31,
            "Morphology kernel size. Larger removes noise but can erase small or distant targets. Effective value is odd.",
        ),
        ControlSpec(
            "open_iters",
            "Open iters",
            "Mask cleanup - advanced",
            0,
            10,
            "Opening removes small white specks from the mask. Keep low unless the mask is noisy.",
        ),
        ControlSpec(
            "close_iters",
            "Close iters",
            "Mask cleanup - advanced",
            0,
            10,
            "Closing fills small holes in the target mask. Increase if the ball appears broken apart.",
        ),
        ControlSpec(
            "focus_mode",
            "Focus mode",
            "Camera focus - advanced",
            0,
            len(FOCUS_MODES) - 1,
            "Camera focus behavior. Continuous is easiest for tuning; manual is better once the distance is known.",
            choices=FOCUS_MODES,
        ),
        ControlSpec(
            "lens_x100",
            "Lens pos",
            "Camera focus - advanced",
            0,
            1000,
            "Manual lens position. Only matters when focus mode is manual. Try small changes while watching sharpness.",
        ),
    ]


def initial_control_values(config: AppConfig) -> Dict[str, int]:
    return {
        "lower_h": config.hsv.lower[0],
        "lower_s": config.hsv.lower[1],
        "lower_v": config.hsv.lower[2],
        "upper_h": config.hsv.upper[0],
        "upper_s": config.hsv.upper[1],
        "upper_v": config.hsv.upper[2],
        "min_area": int(round(config.tracker.min_area)),
        "circularity_pct": int(round(config.tracker.min_circularity * 100.0)),
        "smoothing_pct": int(round(config.tracker.smoothing_alpha * 100.0)),
        "kernel": config.morphology.kernel_size,
        "open_iters": config.morphology.open_iterations,
        "close_iters": config.morphology.close_iterations,
        "focus_mode": FOCUS_MODES.index(config.camera.focus),
        "lens_x100": int(round(config.camera.lens_position * 100.0)),
    }


def draw_detection(frame: np.ndarray, result) -> None:
    height, width = frame.shape[:2]
    center = (width // 2, height // 2)
    cv2.drawMarker(frame, center, (255, 255, 255), markerType=cv2.MARKER_CROSS, markerSize=20, thickness=1)

    if result.detected and result.centroid is not None:
        target = (int(round(result.centroid.x)), int(round(result.centroid.y)))
        cv2.circle(frame, target, 10, (0, 255, 255), 2)
        cv2.line(frame, center, target, (0, 255, 255), 1)


def draw_tuning_status(frame: np.ndarray, config: AppConfig, result) -> None:
    lines = [
        "s: save  q: quit",
        result.to_log_line(),
        f"HSV lower={config.hsv.lower} upper={config.hsv.upper}",
        (
            f"area>={config.tracker.min_area:.0f} "
            f"circ>={config.tracker.min_circularity:.2f} "
            f"smooth={config.tracker.smoothing_alpha:.2f}"
        ),
        (
            f"kernel={config.morphology.kernel_size} "
            f"open={config.morphology.open_iterations} "
            f"close={config.morphology.close_iterations}"
        ),
        f"focus={config.camera.focus} lens={config.camera.lens_position:.2f}",
    ]

    y = 24
    for line in lines:
        cv2.putText(frame, line, (10, y), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 255), 1, cv2.LINE_AA)
        y += 22


def draw_group_header(canvas: np.ndarray, text: str, y: int) -> None:
    cv2.putText(canvas, text, (24, y), cv2.FONT_HERSHEY_SIMPLEX, 0.56, (120, 230, 165), 1)
    cv2.line(canvas, (24, y + 8), (728, y + 8), (68, 76, 82), 1)


def draw_wrapped_text(canvas: np.ndarray, text: str, x: int, y: int, max_chars: int, color: Tuple[int, int, int]) -> None:
    words = text.split()
    lines: List[str] = []
    current = ""
    for word in words:
        candidate = word if not current else f"{current} {word}"
        if len(candidate) > max_chars:
            lines.append(current)
            current = word
        else:
            current = candidate
    if current:
        lines.append(current)

    for line in lines[:2]:
        cv2.putText(canvas, line, (x, y), cv2.FONT_HERSHEY_SIMPLEX, 0.45, color, 1)
        y += 20


def point_in_rect(x: int, y: int, rect: Tuple[int, int, int, int]) -> bool:
    rect_x, rect_y, rect_w, rect_h = rect
    return rect_x <= x <= rect_x + rect_w and rect_y <= y <= rect_y + rect_h


def clamp(value: int, minimum: int, maximum: int) -> int:
    return max(minimum, min(maximum, value))


def clamp_float(value: float, minimum: float, maximum: float) -> float:
    return max(minimum, min(maximum, value))


if __name__ == "__main__":
    raise SystemExit(main())
