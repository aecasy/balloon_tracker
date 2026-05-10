#!/usr/bin/env python3
"""Tune tracker parameters with OpenCV sliders and save them to JSON."""

from __future__ import annotations

import argparse
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

import cv2

from vision_tracker.camera import PiCamera
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

CONTROLS_WINDOW = "controls"
CAMERA_WINDOW = "camera"
MASK_WINDOW = "mask"
FOCUS_MODES = ("none", "continuous", "manual")


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

    tracker = TargetTracker(config.tracker)
    image_size = ImageSize(config.camera.width, config.camera.height)

    create_control_window(config, args.max_area)

    print(f"loaded_config={config_path}", flush=True)
    print("press s to save, q to quit", flush=True)

    last_focus = None
    last_lens_position = None

    try:
        with PiCamera(config.camera) as camera:
            while True:
                live_config = read_control_config(config, args.max_area)
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
    parser = argparse.ArgumentParser(description="Tune green tracker parameters with live sliders.")
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


def create_control_window(config: AppConfig, max_area: int) -> None:
    cv2.namedWindow(CONTROLS_WINDOW)
    cv2.resizeWindow(CONTROLS_WINDOW, 480, 640)

    create_trackbar("lower H", config.hsv.lower[0], 179)
    create_trackbar("lower S", config.hsv.lower[1], 255)
    create_trackbar("lower V", config.hsv.lower[2], 255)
    create_trackbar("upper H", config.hsv.upper[0], 179)
    create_trackbar("upper S", config.hsv.upper[1], 255)
    create_trackbar("upper V", config.hsv.upper[2], 255)
    create_trackbar("min area", int(round(config.tracker.min_area)), max_area)
    create_trackbar("circularity %", int(round(config.tracker.min_circularity * 100.0)), 100)
    create_trackbar("smoothing %", int(round(config.tracker.smoothing_alpha * 100.0)), 100)
    create_trackbar("kernel", config.morphology.kernel_size, 31)
    create_trackbar("open iters", config.morphology.open_iterations, 10)
    create_trackbar("close iters", config.morphology.close_iterations, 10)
    create_trackbar("focus mode", FOCUS_MODES.index(config.camera.focus), len(FOCUS_MODES) - 1)
    create_trackbar("lens x100", int(round(config.camera.lens_position * 100.0)), 1000)


def create_trackbar(name: str, value: int, maximum: int) -> None:
    cv2.createTrackbar(name, CONTROLS_WINDOW, int(clamp(value, 0, maximum)), maximum, noop)


def read_control_config(base_config: AppConfig, max_area: int) -> AppConfig:
    lower = (
        get_trackbar("lower H"),
        get_trackbar("lower S"),
        get_trackbar("lower V"),
    )
    upper = (
        get_trackbar("upper H"),
        get_trackbar("upper S"),
        get_trackbar("upper V"),
    )

    kernel_size = get_trackbar("kernel")
    if kernel_size > 0 and kernel_size % 2 == 0:
        kernel_size += 1

    focus_index = int(clamp(get_trackbar("focus mode"), 0, len(FOCUS_MODES) - 1))

    return AppConfig(
        camera=type(base_config.camera)(
            width=base_config.camera.width,
            height=base_config.camera.height,
            pixel_format=base_config.camera.pixel_format,
            focus=FOCUS_MODES[focus_index],
            lens_position=get_trackbar("lens x100") / 100.0,
        ),
        hsv=HsvRange(lower=lower, upper=upper),
        morphology=MorphologyConfig(
            kernel_size=kernel_size,
            open_iterations=get_trackbar("open iters"),
            close_iterations=get_trackbar("close iters"),
        ),
        tracker=TrackerConfig(
            min_area=float(clamp(get_trackbar("min area"), 0, max_area)),
            min_circularity=get_trackbar("circularity %") / 100.0,
            smoothing_alpha=get_trackbar("smoothing %") / 100.0,
        ),
    )


def get_trackbar(name: str) -> int:
    return cv2.getTrackbarPos(name, CONTROLS_WINDOW)


def draw_detection(frame, result) -> None:
    height, width = frame.shape[:2]
    center = (width // 2, height // 2)
    cv2.drawMarker(frame, center, (255, 255, 255), markerType=cv2.MARKER_CROSS, markerSize=20, thickness=1)

    if result.detected and result.centroid is not None:
        target = (int(round(result.centroid.x)), int(round(result.centroid.y)))
        cv2.circle(frame, target, 10, (0, 255, 255), 2)
        cv2.line(frame, center, target, (0, 255, 255), 1)


def draw_tuning_status(frame, config: AppConfig, result) -> None:
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
        cv2.putText(
            frame,
            line,
            (10, y),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.5,
            (0, 255, 255),
            1,
            cv2.LINE_AA,
        )
        y += 22


def clamp(value: int, minimum: int, maximum: int) -> int:
    return max(minimum, min(maximum, value))


def noop(value: int) -> None:
    return None


if __name__ == "__main__":
    raise SystemExit(main())
