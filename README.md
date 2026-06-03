# CASY Drone Camera Green Ball Tracker

Raspberry Pi camera vision module for detecting a green ball target in live video. The current goal is stable target detection and calibrated bearing output: centroid, pixel offset from image center, detection flag, timestamp, contour quality metrics, and yaw/pitch angles relative to the camera optical axis.

This stage intentionally uses classical vision only:

- Picamera2 camera capture
- OpenCV HSV segmentation
- mask cleanup with morphology
- contour filtering by area and circularity
- centroid smoothing
- optional checkerboard camera calibration
- calibrated yaw/pitch bearing output

ROS publishing comes later. The current runtime emits text or JSON lines that are ready for a later ROS wrapper.

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

## Camera Field Of View

The requested output size can affect the sensor mode Picamera2 chooses. A 4:3 output such as `640x480` may use a cropped view. To ask Camera Module 3 for a wide 16:9 sensor mode while still processing a smaller frame, pass a matching raw sensor size:

```bash
python3 scripts/cam_test.py --width 1280 --height 720 --raw-width 2304 --raw-height 1296
```

If the view looks wider with this command, keep the raw mode. In testing, this recovered a wider horizontal field of view than the default `640x480` setup.

Processing cost depends mostly on the `main` output size, not just the raw sensor size. For example, `1280x720` processes about three times as many pixels as `640x480`, so HSV masking, morphology, contour finding, scoring, and debug drawing all get heavier. For maximum field of view with lower CPU cost, keep the wide raw mode and use a smaller 16:9 processed frame:

```bash
python3 scripts/green_tracker.py --width 640 --height 360 --raw-width 2304 --raw-height 1296 --method scored --output json --headless
```

Good speed/detail tradeoffs:

```text
640x360   fastest, still wide field of view
960x540   middle ground
1280x720  sharper, slower
```

For best runtime efficiency:

- use `--headless` for final runs
- keep `shading_enabled` off unless actively testing it
- keep `--raw-width 2304 --raw-height 1296` for the wide sensor readout
- use the smallest 16:9 `--width` and `--height` that still detects the ball reliably
- avoid unnecessarily large morphology kernel/open/close values
- if CPU is still tight, disable heavier scoring components first, especially `shading` and then `color_fill`

Use the same camera geometry for tuning, calibration, and final runtime. If you change `width`, `height`, `raw_width`, or `raw_height`, recalibrate before trusting `yaw_deg` and `pitch_deg`. Do not use a `1280x720` calibration file for a `640x360` tracker run, even though both are 16:9; the calibration values are in pixels and depend on the exact output mode.

```bash
python3 scripts/tune_tracker.py --width 1280 --height 720 --raw-width 2304 --raw-height 1296
python3 scripts/calibrate_camera.py --width 1280 --height 720 --raw-width 2304 --raw-height 1296 --pattern-cols 6 --pattern-rows 8 --square-size-mm 35.8
python3 scripts/green_tracker.py --width 1280 --height 720 --raw-width 2304 --raw-height 1296 --method scored --output json --headless
```

Recommended efficient wide-FOV workflow:

```bash
python3 scripts/tune_tracker.py --width 640 --height 360 --raw-width 2304 --raw-height 1296
python3 scripts/calibrate_camera.py --width 640 --height 360 --raw-width 2304 --raw-height 1296 --pattern-cols 6 --pattern-rows 8 --square-size-mm 35.8
python3 scripts/green_tracker.py --width 640 --height 360 --raw-width 2304 --raw-height 1296 --method scored --output json --headless
```

After changing to a wider view, the ball may occupy fewer pixels than before. Retune `min_area` if the tracker starts missing far-away targets. HSV usually stays similar, but area thresholds and scoring weights may need a small adjustment.

This can prevent accidental software cropping, but it cannot exceed the physical lens field of view. Camera Module 3 Standard is much narrower than Camera Module 3 Wide.

## Candidate Scoring

The legacy tracker chooses the largest contour that passes `min_area` and `min_circularity`. The scored tracker keeps the same HSV mask and contour pipeline, then ranks every valid contour with a weighted score. This helps choose the object that looks most ball-like instead of blindly choosing the largest or first valid green blob.

Only enabled scoring components with positive weights participate in the final score:

```text
final_score = sum(component_score * component_weight) / sum(active_component_weights)
```

If a component is disabled, it is shown as `off` and ignored. If every component is disabled or every active weight is zero, scored detection returns no target. The selected candidate must also pass `min_score`.

All component scores are clamped to the range `0.0` to `1.0`, where `1.0` is best.

`color_fill`

Measures how much of the contour's filled area is actually green in the HSV mask. The tracker creates a filled contour mask inside the contour bounding box, then counts green pixels inside it.

```text
color_fill = green_pixels_inside_contour / total_pixels_inside_contour
```

This is useful because the target should be mostly green. It can be more expensive than simple contour geometry because it inspects mask pixels inside the candidate region.

`circularity`

Measures the classic contour roundness score:

```text
circularity = 4 * pi * contour_area / perimeter^2
```

A perfect circle approaches `1.0`. Long, jagged, or irregular shapes score lower. This score is sensitive to contour noise, highlights, shadows, and partial occlusion, so it is useful but not always reliable by itself.

`circle_fit`

Measures how well the contour boundary fits around a circle. The tracker finds the minimum enclosing circle, measures the distance from each contour point to the circle center, then looks at how consistent those distances are.

```text
normalized_error = std(distance_from_center_to_each_contour_point) / radius
circle_fit = 1 - normalized_error
```

A clean round object has contour points at similar radii, so the standard deviation is small and the score is high. An elongated object like a pen usually has a larger radius error and scores lower. This is often a stronger "ball-like outline" cue than plain circularity.

`enclosing_fill`

Measures how much of the candidate's minimum enclosing circle is filled by the contour area:

```text
enclosing_fill = contour_area / (pi * enclosing_circle_radius^2)
```

A filled circular blob scores high. Thin arcs, crescent shapes, and sparse irregular blobs score lower. This is scale-independent, so it does not reject far-away balls just because they are small.

`solidity`

Measures how completely the contour fills its convex hull:

```text
solidity = contour_area / convex_hull_area
```

Solid compact objects score near `1.0`. Shapes with dents, holes, or concave edges score lower. This helps reject broken mask fragments and irregular reflections, but a non-ball solid object can still score well here, so solidity should be combined with roundness scores.

`relative_area`

Compares each valid candidate's area against the largest valid candidate in the same frame:

```text
relative_area = candidate_area / largest_valid_candidate_area
```

This is not a fixed size gate. It only says, "among the green candidates already passing `min_area`, prefer the dominant one." That helps a real ball beat small green noise without preventing far-away ball detection.

`shading`

Optional experimental cue for sphere-like lighting. It inspects the HSV `V` channel inside the contour, estimates brightness smoothness from image gradients, and mixes that with brightness variation:

```text
smoothness = 1 - clamp(mean_gradient / 64)
contrast = clamp(std(value_pixels) / 64)
shading = (0.7 * smoothness) + (0.3 * contrast)
```

For very small candidates below `shading_min_area`, or when no frame is available, it returns neutral `0.5` so tiny far-away balls are not punished. This score is off by default because it costs more CPU and can be lighting-dependent.

## Calibrate

Once tracking is stable, calibrate each camera with the checkerboard before using yaw/pitch bearings. Calibration is tied to the exact camera geometry, so use the same `width`, `height`, `raw_width`, `raw_height`, and focus setup for tuning, calibration, and final tracking. A calibration captured at `1280x720` is not interchangeable with a `640x360` tracker run unless you intentionally add and validate a calibration-scaling workflow.

For your 6 by 8 inner-corner board with 35.8 mm squares:

```bash
python3 scripts/calibrate_camera.py --pattern-cols 6 --pattern-rows 8 --square-size-mm 35.8
```

For the recommended efficient wide-FOV setup:

```bash
python3 scripts/calibrate_camera.py \
  --width 640 \
  --height 360 \
  --raw-width 2304 \
  --raw-height 1296 \
  --pattern-cols 6 \
  --pattern-rows 8 \
  --square-size-mm 35.8
```

In the calibration window:

1. Show the checkerboard to the camera.
2. Wait until corners are detected and drawn.
3. Press `c` to capture a sample.
4. Move and tilt the board around: center, corners, edges, closer, farther, and angled.
5. Capture at least 15 samples, ideally 20-25.
6. Press `k` to calibrate and save.
7. Press `q` to quit.

By default calibration saves to:

```text
config/camera_calibration.json
```

When calibrating multiple cameras, save each camera separately so the next run does not overwrite the previous calibration:

```bash
python3 scripts/calibrate_camera.py --width 640 --height 360 --raw-width 2304 --raw-height 1296 --pattern-cols 6 --pattern-rows 8 --square-size-mm 35.8 --output config/camera_calibration_left.json
python3 scripts/calibrate_camera.py --width 640 --height 360 --raw-width 2304 --raw-height 1296 --pattern-cols 6 --pattern-rows 8 --square-size-mm 35.8 --output config/camera_calibration_right.json
```

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

Run with a specific camera calibration:

```bash
python3 scripts/green_tracker.py \
  --width 640 \
  --height 360 \
  --raw-width 2304 \
  --raw-height 1296 \
  --method scored \
  --output json \
  --headless \
  --calibration config/camera_calibration_left.json
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
    calibration.py
    camera.py
    color_detector.py
    config.py
    geometry.py
    tracker.py
tests/
  test_calibration.py
  test_config.py
  test_geometry.py
  test_scoring.py
requirements-notes.md
```
