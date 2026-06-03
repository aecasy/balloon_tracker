# Codex Handoff Summary — CASY Drone Camera

## Project goal

Build a Raspberry Pi camera-based vision module for a drone. The module should detect a simple colored target in live video, compute the target centroid in image coordinates, and eventually convert that centroid into **horizontal and vertical bearing angles** relative to the camera optical axis. The system does **not** need distance/range estimation, 3D reconstruction, SLAM, or neural-network detection at this stage. The final output should be suitable for ROS / downstream control integration, for example yaw angle, pitch angle, detection flag, timestamp, and optional quality metrics. 

---

## Tech stack

Current development setup:

```text
Hardware:
- Raspberry Pi 4
- Raspberry Pi Camera Module 3
- Green ball target

Current OS:
- Ubuntu 26.04 on Raspberry Pi 4

Camera stack:
- rpicam-apps
- Picamera2
- libcamera
- Raspberry Pi Camera Module 3 detected as imx708

Vision:
- Python 3
- OpenCV
- NumPy
- HSV color segmentation
- contour detection
- centroid extraction
```

Final intended deployment:

```text
- Raspberry Pi 4
- Ubuntu Server 20.04
- ROS Noetic
- Headless operation
- ROS node publishing target bearing
```

Important deployment risk: Ubuntu 26.04 is being used for bring-up, but final ROS Noetic deployment is expected on Ubuntu 20.04, where the Pi Camera Module 3 / libcamera / Picamera2 stack may require extra setup. 

---

## Repo structure

Current expected minimal repo structure:

```text
casy-drone-camera/
├── README.md
├── LICENSE
├── docs/
│   └── CASY_Drone_Camera_Project_Specifications.md
├── scripts/
│   ├── cam_test.py
│   ├── hsv_probe.py
│   └── green_tracker.py
└── requirements-notes.md
```

Current actual status may be simpler, possibly just loose Python files. Codex should help organize into this structure.

Suggested future structure:

```text
casy-drone-camera/
├── README.md
├── LICENSE
├── docs/
│   ├── project_specifications.md
│   ├── calibration_notes.md
│   └── ros_integration_plan.md
├── scripts/
│   ├── cam_test.py
│   ├── hsv_probe.py
│   ├── green_tracker.py
│   └── calibrate_camera.py
├── src/
│   ├── vision_tracker/
│   │   ├── __init__.py
│   │   ├── camera.py
│   │   ├── color_detector.py
│   │   ├── tracker.py
│   │   └── geometry.py
│   └── ros_nodes/
│       └── target_bearing_node.py
└── tests/
    └── test_geometry.py
```

---

## Current implementation status

Working:

```text
- rpicam-hello successfully opens camera preview.
- Camera Module 3 is detected as imx708.
- Picamera2 imports successfully in Python.
- Python OpenCV live camera window works.
- Green ball HSV values have been sampled.
- Green ball shape and centroid are currently recognized decently.
```

Current tracking approach:

```text
1. Capture image using Picamera2.
2. Convert image to HSV.
3. Threshold green target.
4. Clean mask using morphology.
5. Find contours.
6. Filter by minimum area and circularity.
7. Select largest valid contour.
8. Compute centroid using image moments.
9. Compute dx, dy from image center.
10. Display debug camera and mask windows.
```

Current target:

```text
green ball
```

Current HSV range:

```python
lower_green = np.array([68, 180, 20])
upper_green = np.array([88, 255, 255])
```

Current recommended resolution:

```python
main={"size": (640, 480), "format": "RGB888"}
```

---

## Commands to install / run / test

Install packages on current Ubuntu 26.04 Pi:

```bash
sudo apt update
sudo apt install -y rpicam-apps python3-picamera2 python3-opencv
```

Do **not** use plain system-wide pip for Picamera2:

```bash
pip install picamera2
```

This fails on modern Ubuntu because of externally managed Python environments.

Camera hardware test:

```bash
rpicam-hello
```

Picamera2 import test:

```bash
python3 -c "from picamera2 import Picamera2; print('picamera2 ok')"
```

Run basic camera feed:

```bash
python3 scripts/cam_test.py
```

Run HSV probe:

```bash
python3 scripts/hsv_probe.py
```

Run tracker:

```bash
python3 scripts/green_tracker.py
```

Current testing is manual. There are no automated tests yet.

Manual success criteria:

```text
- Live camera window opens.
- Green ball appears white in mask.
- Yellow / unrelated objects are mostly rejected.
- One contour surrounds the ball.
- Centroid stays near ball center.
- dx and dy change logically when the ball moves.
- No random jumps to background objects.
```

---

## Key files and what they do

### `docs/CASY_Drone_Camera_Project_Specifications.md`

Project specification document. Describes final desired system, current development setup, target behavior, current HSV values, deployment gap between Ubuntu 26.04 and Ubuntu 20.04 / ROS Noetic, and future development milestones. 

### `scripts/cam_test.py`

Minimal Picamera2 + OpenCV live preview test.

Purpose:

```text
Verify that Python can access the Pi Camera Module 3 and show frames in an OpenCV window.
```

### `scripts/hsv_probe.py`

Interactive HSV sampler.

Purpose:

```text
Click on the target in the camera window and print BGR / HSV values for tuning color thresholds.
```

### `scripts/green_tracker.py`

Current main tracker.

Purpose:

```text
Detect the green ball, compute centroid, smooth the centroid, filter by area/circularity, display debug windows, and print detected/dx/dy/area/circularity.
```

Expected output format:

```text
detected=True dx=42 dy=-18 area=5320 circularity=0.81
```

---

## Recent decisions

```text
- Current target changed from red balloon to green ball.
- Current development platform is Raspberry Pi 4 + Pi Camera Module 3 + Ubuntu 26.04.
- Final target deployment remains Ubuntu 20.04 Server because of ROS Noetic.
- Use Picamera2 instead of cv2.VideoCapture(0).
- Use apt packages, not pip, for Picamera2 on Ubuntu 26.04.
- Use HSV segmentation and contour tracking, not ML.
- Work at 640x480 for speed and easier debugging.
- Add target-lost behavior, smoothing, area filtering, and circularity filtering before calibration.
- Calibrate only after centroid tracking is stable.
```

---

## Open tasks

Immediate:

```text
1. Clean up repo structure.
2. Move loose scripts into scripts/.
3. Add README with install/run instructions.
4. Make green_tracker.py configurable:
   - HSV bounds
   - min area
   - min circularity
   - smoothing alpha
   - resolution
   - autofocus/manual focus
5. Add command-line arguments or config file.
6. Add target-lost handling if not already fully implemented.
7. Improve logging format.
8. Confirm stable centroid behavior under small lighting and distance changes.
```

Next:

```text
1. Add optional manual focus setting for Camera Module 3.
2. Add optional exposure/white-balance locking for more stable HSV detection.
3. Add camera calibration workflow.
4. Save calibration file with fx, fy, cx, cy, and distortion coefficients.
5. Convert centroid pixels to yaw/pitch bearing angles.
6. Add unit tests for pixel-to-angle math.
7. Start ROS Noetic wrapper design.
8. Plan migration path from Ubuntu 26.04 to Ubuntu 20.04 Server.
```

Later:

```text
1. Implement ROS Noetic node.
2. Publish target_bearing topic.
3. Remove GUI dependencies for headless deployment.
4. Add optional debug image publishing.
5. Decide final communication path to Simulink / guidance system.
```

---

## Known errors / issues encountered

### `libatlas-base-dev` unavailable

Command failed:

```bash
sudo apt install -y python3-pip python3-opencv libatlas-base-dev
```

Error:

```text
Package libatlas-base-dev is not available
```

Decision:

```text
Do not use libatlas-base-dev. It is unnecessary for the current tracker.
Use python3-opencv from apt.
```

### `libcamera-apps` not found

Command failed:

```bash
sudo apt install -y libcamera-apps python3-libcamera
```

Error:

```text
Unable to locate package libcamera-apps
```

Decision:

```text
Use rpicam-apps instead.
```

Working command:

```bash
sudo apt install -y rpicam-apps python3-picamera2 python3-opencv
```

### `pip install picamera2` failed

Error:

```text
externally-managed-environment
```

Decision:

```text
Use apt package python3-picamera2.
Do not break system Python with --break-system-packages.
```

### Color channel confusion

Issue:

```text
Yellow objects appeared blue in the capture window.
```

Likely cause:

```text
Unnecessary RGB/BGR conversion.
```

Current practical rule:

```python
frame = picam2.capture_array()
hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
```

Do not add conversion unless colors display incorrectly.

### Focus issue

Issue:

```text
Camera image initially appeared out of focus.
```

Cause:

```text
Raspberry Pi Camera Module 3 has software-controlled autofocus.
```

Development option:

```python
from libcamera import controls

picam2.set_controls({
    "AfMode": controls.AfModeEnum.Continuous
})
```

Future tracking option:

```python
picam2.set_controls({
    "AfMode": controls.AfModeEnum.Manual,
    "LensPosition": 2.0
})
```

---

## What to ask Codex to do next

Ask Codex:

```text
Please organize this repository into a clean Python project for the Raspberry Pi green ball tracker.

Tasks:
1. Create the repo structure:
   - docs/
   - scripts/
   - src/vision_tracker/
   - tests/
2. Move the current green_tracker.py logic into reusable modules:
   - camera.py for Picamera2 setup/capture
   - color_detector.py for HSV mask creation
   - tracker.py for contour filtering and centroid tracking
   - geometry.py for dx/dy and future pixel-to-angle conversion
3. Keep scripts/green_tracker.py as a runnable entrypoint.
4. Add CLI arguments for HSV bounds, min area, circularity, smoothing alpha, resolution, and autofocus/manual focus.
5. Add clean printed output:
   detected=<bool> dx=<int|None> dy=<int|None> area=<int> circularity=<float>
6. Add README.md with install and run commands for Ubuntu 26.04 on Raspberry Pi 4.
7. Add a placeholder calibration workflow section.
8. Add basic tests for geometry.py.
9. Do not add ROS yet.
10. Do not change the detection algorithm away from HSV + contours.
```

Most important instruction for Codex:

```text
Do not jump to ROS or camera calibration yet. First make the current green ball tracker clean, configurable, and stable.
```
