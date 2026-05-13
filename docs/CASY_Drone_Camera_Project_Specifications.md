# CASY Drone Camera Project Specifications

## Goal

Build a Raspberry Pi camera-based vision module for a drone. The module detects a simple colored target in live video, computes the target centroid in image coordinates, and later converts that centroid into horizontal and vertical bearing angles relative to the camera optical axis.

The current phase does not include distance estimation, 3D reconstruction, SLAM, neural-network detection, ROS integration, or camera calibration code.

## Current Target

- Green ball
- HSV segmentation
- Contour filtering
- Centroid extraction

Current HSV range:

```python
lower_green = (68, 180, 20)
upper_green = (88, 255, 255)
```

Runtime and tuning parameters are stored in:

```text
config/green_tracker.json
```

## Hardware

- Raspberry Pi 4
- Raspberry Pi Camera Module 3
- Green ball target

## Current Development Setup

- Ubuntu 26.04 on Raspberry Pi 4
- `rpicam-apps`
- Picamera2
- libcamera
- OpenCV
- NumPy

Known working camera configuration:

```python
main={"size": (640, 480), "format": "RGB888"}
```

## Final Deployment Target

- Raspberry Pi 4
- Ubuntu Server 20.04
- ROS Noetic
- Headless operation
- ROS node publishing target bearing

Deployment risk: Ubuntu 20.04 plus Raspberry Pi Camera Module 3 and Picamera2/libcamera may require extra setup. Do not assume the Ubuntu 26.04 bring-up stack will transfer directly.

## Tracker Output

The immediate tracker output is:

```text
detected=<bool> dx=<int|None> dy=<int|None> area=<int> circularity=<float>
```

The scored detector appends:

```text
score=<float> color_fill=<float> enclosing_fill=<float> solidity=<float> shading=<float>
```

Definitions:

- `detected`: whether a valid target contour was found.
- `dx`: horizontal pixel offset from image center. Positive means target is right of center.
- `dy`: vertical pixel offset from image center. Positive means target is above center.
- `area`: selected contour area in pixels.
- `circularity`: selected contour circularity from 0 to 1.

## Current Algorithm

1. Capture frame from Picamera2.
2. Convert frame from BGR to HSV.
3. Threshold green pixels.
4. Clean the mask with morphology.
5. Find external contours.
6. Reject contours below minimum area.
7. Reject contours below minimum circularity.
8. Select the largest remaining contour.
9. Compute centroid from image moments.
10. Smooth the centroid.
11. Compute `dx` and `dy` from image center.
12. Print one tracking line per frame.

## Candidate Scoring

The original legacy method selects the largest contour that passes area and circularity thresholds. The scored method ranks every candidate that passes the area cleanup gate using:

- color fill inside the candidate
- circularity
- enclosing-circle fill
- solidity
- optional sphere-like shading score

The scored method does not use a fixed radius or fixed object-size gate. Area is used only as the existing cleanup threshold and as a tie-breaker when candidates have equal scores.

Scoring components can be enabled or disabled in `config/green_tracker.json` and the tuning UI. Disabled components are not included in the weighted score. Expensive components such as color-fill ROI scoring and shading analysis should be disabled when testing Pi performance.

## Tuning Workflow

1. Run `python3 scripts/tune_tracker.py`.
2. Start with the `Target color` group and tune HSV until the ball is white in the mask.
3. Use `Detection quality` to reject specks and unstable contours.
4. Use `Mask cleanup` only if the mask is noisy or the target has holes.
5. Use `Camera focus` only if the image is visibly soft.
6. Hover over controls in the tuning window for help text.
7. Press `s` to save the current settings to `config/green_tracker.json`.
8. Run `python3 scripts/green_tracker.py`; it loads the saved config automatically.

To compare old and new methods live, run:

```bash
python3 scripts/compare_trackers.py
```

## Immediate Milestones

1. Keep the tracker clean and configurable.
2. Tune HSV, area, circularity, smoothing, and focus options on hardware.
3. Confirm stable centroid behavior under lighting and distance changes.
4. Add calibration only after target tracking is stable.
5. Add ROS only after calibrated bearing math is working.
