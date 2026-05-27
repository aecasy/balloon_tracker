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
- optional TCP debug streaming for headless calibration/tuning
- ROS Noetic bridge through Docker

The current deployment runs the camera tracker natively on Raspberry Pi OS Lite and pipes JSON output into a ROS Noetic Docker container. The container publishes calibrated yaw/pitch data on `/target_bearing`.

## Hardware

- Raspberry Pi 4
- Raspberry Pi Camera Module 3
- Green ball target

## Current Runtime Architecture

The Raspberry Pi Camera Module 3 requires the modern Raspberry Pi camera stack. The old Ubuntu 20.04 Server image used for ROS Noetic does not expose the IMX708 camera driver or overlay on its 5.4 Raspberry Pi kernel, so the camera cannot run there directly.

Current deployment model:

```text
Raspberry Pi 4
  Raspberry Pi OS Lite 64-bit host
    Picamera2 / libcamera / rpicam-apps
    native Python tracker
    calibrated JSON bearing output
    Docker engine
      ROS Noetic container
      /target_bearing publisher
```

The Windows development machine is used over SSH and for the optional remote OpenCV viewer.

Install the camera and vision packages with apt:

```bash
sudo apt update
sudo apt full-upgrade -y
sudo apt install -y git rpicam-apps python3-picamera2 python3-opencv python3-numpy
```

Do not install Picamera2 with plain system-wide pip. Use `python3-picamera2` from apt so it matches the Raspberry Pi camera stack.

## Legacy Ubuntu 20.04 Image Migration

The previous Ubuntu 20.04 Server image cannot be used as the host OS for Camera Module 3 capture, but its non-camera deployment pieces still matter. See `docs/Legacy_Ubuntu20_Scan.md` for the scanned services, scripts, topics, ports, and package clues.

The image notes say it included:

- startup Python script for MAVLink communication with the flight controller
- startup Python script for RC channel 1-4 override gated by RC channel 7
- startup Python script for Pi shutdown when RC channel 8 is high
- ROS1 installation with a `catkin_ws` for Simulink connection
- `micro` editor

Those services need to be reproduced on the new Raspberry Pi OS Lite host or moved into Docker containers. Credentials and image backup details should stay in private notes, not in this repository.

Migration target:

```text
camera tracker on Pi OS Lite host
  -> /target_bearing in ROS Noetic Docker
  -> MAVLink / flight-controller integration
  -> Simulink-facing ROS connection to the remote Windows PC
```

The migrated Pi OS Lite deployment is configured to use the dedicated Ubuntu OptiTrack PC as ROS master:

```text
ROS_MASTER_URI=http://192.168.1.154:11311
ROS_IP=192.168.1.168
```

Pi-specific deployment files live in `deploy/pi_os_lite/`. They include:

- environment template for the new Pi network, camera, MAVLink, and tracker settings
- native MAVProxy launcher for `/dev/serial0` at `921600`
- native CH8 shutdown listener
- Docker ROS bridge services for `quad_commands` RC override and CH7 `autonomy_enable`
- systemd units for boot startup

## Roadmap

1. Recreate the Ubuntu 20.04 image's MAVLink, RC override, shutdown, ROS, and Simulink-facing behavior on the Pi OS Lite + Docker deployment.
2. Add boot automation for Docker ROS core and the piped tracker.
3. Validate `/target_bearing` consumption by the flight-controller or Simulink control path.
4. Future quality-of-life task: support `ROS_IP=auto` in the Pi OS Lite env file by resolving the local source IP used to reach `ROS_MASTER_URI`, parsing the value after `src` from `ip -4 route get <ros-master-host>`.
5. Last task: move from the current green-ball workflow to full-resolution tracking of the final red balloon target.

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

## Headless Remote Streaming

When running on a headless OS (like Raspberry Pi OS Lite) where no desktop environment exists, OpenCV's native `imshow` windows will fail. To bypass this, the tracker has a built-in TCP streamer.

1. **Start the Stream Server on the Pi:**
   Run your tracker or calibration script with the `--stream-port` flag:
   ```bash
   python3 scripts/calibrate_camera.py --stream-port 5000
   ```
   *(or use `scripts/green_tracker.py --stream-port 5000`)*

2. **Connect from Windows:**
   On your Windows PC (or any machine with a GUI and OpenCV installed), run the viewer script:
   ```bash
   python scripts/remote_viewer.py --ip <RASPBERRY_PI_IP> --port 5000
   ```
   This will pop open an OpenCV window on your PC showing the live feed. Any keys you press in this window (like `c` for capture or `q` for quit) will be sent over the network to the script running on the Pi.

## ROS Docker Integration

To run ROS Noetic nodes alongside the native vision tracker on modern Raspberry Pi OS, use Docker. In the migrated flight setup, `roscore` runs on the dedicated Ubuntu OptiTrack PC at `192.168.1.154`; the Pi containers connect to that remote ROS master.

### 1. Install Docker on PiOS Lite
If you are running a fresh PiOS Lite image, install Docker and configure your user permissions:
```bash
curl -fsSL https://get.docker.com -o get-docker.sh && sudo sh get-docker.sh
sudo usermod -aG docker $USER
newgrp docker
```

### 2. Build the ROS Docker Image
```bash
docker build -t casy-ros-node -f Dockerfile.ros .
```

### 3. Run the ROS Master
For the flight setup, start `roscore` on the Ubuntu OptiTrack PC, not on the Pi. For bench testing without the OptiTrack PC, the compose file still provides an optional local ROS master:

```bash
docker compose --profile bench up -d roscore
```

### 4. Run the ROS Bridge Nodes

With `/etc/casy-drone/pi_os_lite.env` present on the Pi:

```bash
docker compose --env-file /etc/casy-drone/pi_os_lite.env up rc-override rc-ch7
```

`rc-override` subscribes to `quad_commands` and sends MAVLink RC override through MAVProxy. `rc-ch7` reads RC channel 7 and publishes `autonomy_enable`.

### 5. Run the Piped Tracker
Run the native Python vision tracker and pipe its JSON output directly into the ROS publisher container. Because the standard output is piped, **this command will intentionally produce no terminal output**:
```bash
python3 scripts/green_tracker.py \
  --width 1280 \
  --height 720 \
  --raw-width 2304 \
  --raw-height 1296 \
  --method scored \
  --output json \
  --headless \
  --calibration config/camera_calibration_1280x720_raw2304x1296.json \
  | docker run -i --rm --network host \
      -e ROS_MASTER_URI=http://192.168.1.154:11311 \
      -e ROS_IP=192.168.1.168 \
      casy-ros-node
```

The Pi OS Lite deployment wrapper runs the same pipeline with the configured remote ROS master:

```bash
deploy/pi_os_lite/run_tracker_pipeline.sh
```

### 6. Debugging ROS Topics
Because `docker exec` does not automatically load the ROS environment variables, you cannot simply run `docker exec ... rostopic echo` directly. To make this easy, use the provided helper script in a **second terminal**. It uses a local `roscore` container when one is running, otherwise it starts a temporary `casy-ros-node` container with `/etc/casy-drone/pi_os_lite.env`.
```bash
# Make sure the script is executable first
chmod +x scripts/ros_exec.sh

# Verify coordinate stream
./scripts/ros_exec.sh rostopic echo /target_bearing

# Check publish rate (FPS)
./scripts/ros_exec.sh rostopic hz /target_bearing
```

## Pi OS Lite Deployment

On the new Pi (`casy@192.168.1.168`), pull the branch and install the migration support files:

```bash
cd ~/balloon_tracker
git pull
chmod +x deploy/pi_os_lite/*.sh
deploy/pi_os_lite/install.sh
```

Log out and back in after `install.sh` so the `docker` group membership applies. Then review the environment file:

```bash
sudo nano /etc/casy-drone/pi_os_lite.env
```

Run the preflight checks before enabling boot services:

```bash
deploy/pi_os_lite/preflight.sh
```

With propellers removed, start services one at a time:

```bash
sudo systemctl enable --now casy-mavproxy.service
sudo systemctl enable --now casy-ch8-shutdown.service
sudo systemctl enable --now casy-ros-bridges.service
sudo systemctl enable --now casy-tracker-pipeline.service
```

Useful logs:

```bash
journalctl -u casy-mavproxy.service -f
journalctl -u casy-ros-bridges.service -f
journalctl -u casy-tracker-pipeline.service -f
```

The copied Simulink-generated catkin packages are built into the ROS Docker image, but no generated Simulink node is auto-started yet. Choose and validate the active generated package before adding it to boot automation.

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
Dockerfile.ros
docker-compose.yml
deploy/
  pi_os_lite/
    pi_os_lite.env.example
    install.sh
    preflight.sh
    run_mavproxy.sh
    run_tracker_pipeline.sh
    shutdown_on_ch8.py
    sudoers.d/
    systemd/
docs/
  Agent_Handoff_Phase2.md
  CASY_Drone_Camera_Project_Specifications.md
  ChatGPT handoff.md
  calibration_notes.md
config/
  camera_calibration_1280x720_raw2304x1296.json
  green_tracker.json
scripts/
  cam_test.py
  calibrate_camera.py
  compare_trackers.py
  green_tracker.py
  hsv_probe.py
  remote_viewer.py
  ros_exec.sh
  tune_tracker.py
src/
  ros_nodes/
    ros_rc_bridge.py
    ros_rc_ch7_read.py
    target_bearing_node.py
  vision_tracker/
    __init__.py
    calibration.py
    camera.py
    color_detector.py
    config.py
    geometry.py
    streamer.py
    tracker.py
tests/
  test_calibration.py
  test_config.py
  test_geometry.py
  test_pi_os_lite_migration.py
  test_scoring.py
requirements-notes.md
```
