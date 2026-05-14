# CASY Drone Camera Green Ball Tracker

Raspberry Pi camera vision module for detecting a green ball target in live video. The current goal is stable 2D target detection: centroid, pixel offset from image center, detection flag, timestamp, and contour quality metrics.

This stage intentionally uses classical vision only:

- Picamera2 camera capture
- OpenCV HSV segmentation
- mask cleanup with morphology
- contour filtering by area and circularity
- centroid smoothing

ROS, calibration, and bearing-angle publishing come later.

## Hardware

- Raspberry Pi 4
- Raspberry Pi Camera Module 3
- Green ball target

## Current Bring-Up OS

Ubuntu 26.04 on Raspberry Pi 4.

Install the camera and vision packages with apt:

```bash
sudo apt update
sudo apt install -y rpicam-apps python3-picamera2 python3-opencv
```

Do not install Picamera2 with plain system-wide pip on modern Ubuntu. Use `python3-picamera2` from apt.

## Quick Checks

Camera hardware preview:

```bash
rpicam-hello
```

Picamera2 import:

```bash
python3 -c "from picamera2 import Picamera2; print('picamera2 ok')"
```

## Run

Basic camera preview:

```bash
python3 scripts/cam_test.py
```

Interactive HSV probe:

```bash
python3 scripts/hsv_probe.py
```

Live tracker tuning with sliders:

```bash
python3 scripts/tune_tracker.py
```

The tuner opens camera, mask, and grouped controls windows. Hover over any control to see what it does.

The most important controls are in the first two groups:

- `Target color`: HSV bounds. Start here.
- `Detection quality`: area, circularity, and smoothing.

The advanced groups are useful only when needed:

- `Mask cleanup`: morphology kernel/open/close for noisy masks.
- `Camera focus`: autofocus/manual focus settings for the Camera Module 3.

The `Scoring` group has on/off controls for each scoring component. Turning a component off removes it from the score and avoids its calculation. `Color fill` and `Shading` are the most image/ROI-heavy; `Shading` stays off by default.

Move the sliders until the green ball is isolated cleanly in the mask, then press `s` to save the current parameters to:

```text
config/green_tracker.json
```

Press `q` to quit.

Compare the old and new candidate selection methods live:

```bash
python3 scripts/compare_trackers.py
```

In the comparison window, `legacy` is the old largest-valid-contour method and `scored` is the new weighted candidate scorer. The candidate table shows the top scored candidates and their component values.

## Calibrate

Once tracking is stable, calibrate the camera with the checkerboard before using yaw/pitch bearings.

For your 6 by 8 inner-corner board with 35.8 mm squares:

```bash
python3 scripts/calibrate_camera.py --pattern-cols 6 --pattern-rows 8 --square-size-mm 35.8
```

Move the checkerboard through different parts of the image and tilt it at different angles. Press `c` when corners are detected to capture a sample. Capture at least 15-25 samples, then press `k` to calibrate and save:

```text
config/camera_calibration.json
```

Press `q` to quit.

Green ball tracker:

```bash
python3 scripts/green_tracker.py
```

The tracker reads `config/green_tracker.json` by default. It still uses the legacy method unless you ask for the new scorer:

```bash
python3 scripts/green_tracker.py --method scored --log-components
```

Run the final headless bearing output as JSON:

```bash
python3 scripts/green_tracker.py --method scored --output json --headless
```

If you need to run before calibration, pass:

```bash
python3 scripts/green_tracker.py --method scored --output json --headless --allow-uncalibrated
```

Without calibration, `yaw_deg` and `pitch_deg` are `null`.

Use CLI flags only when you want a temporary override without changing the saved file.

Example with explicit settings:

```bash
python3 scripts/green_tracker.py \
  --width 640 \
  --height 480 \
  --lower-hsv 68,180,20 \
  --upper-hsv 88,255,255 \
  --min-area 300 \
  --min-circularity 0.55 \
  --smoothing-alpha 0.35 \
  --focus continuous
```

Use a different config file:

```bash
python3 scripts/green_tracker.py --config config/green_tracker.json
python3 scripts/tune_tracker.py --config config/green_tracker.json
```

Headless-style run without debug windows:

```bash
python3 scripts/green_tracker.py --no-display
```

Expected output:

```text
detected=True dx=42 dy=-18 area=5320 circularity=0.81
```

When the target is lost:

```text
detected=False dx=None dy=None area=0 circularity=0.00
```

## Tests

The current automated tests cover camera-independent geometry helpers:

```bash
python -m unittest discover -s tests
```

On the Raspberry Pi you may prefer:

```bash
python3 -m unittest discover -s tests
```

## Project Structure

```text
docs/
  CASY_Drone_Camera_Project_Specifications.md
  ChatGPT handoff.md
  calibration_notes.md
config/
  green_tracker.json
scripts/
  cam_test.py
  calibrate_camera.py
  green_tracker.py
  hsv_probe.py
  compare_trackers.py
  tune_tracker.py
src/
  vision_tracker/
    __init__.py
    camera.py
    color_detector.py
    config.py
    geometry.py
    tracker.py
tests/
  test_geometry.py
requirements-notes.md
```

## Calibration Placeholder

The tracker currently reports pixel offsets only. After centroid tracking is stable, add camera calibration to estimate `fx`, `fy`, `cx`, `cy`, and distortion coefficients. Then convert centroid position into yaw and pitch bearing angles.

For now, do not add ROS or calibration code until the green target detection is reliable under realistic lighting and distance changes.
