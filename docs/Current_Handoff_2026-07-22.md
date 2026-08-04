# Current Handoff - 2026-07-22

This file captures the latest known project state after resuming work on 2026-07-22.

## Repo State

- GitHub repository: `https://github.com/aecasy/balloon_tracker.git`
- Active migration branch: `feat/ros-docker`
- Last known pushed work before this handoff: `33923e2 Add next work day report`
- Main migration references:
  - `docs/CASY_Drone_Camera_Project_Specifications.md`
  - `docs/Pi_OS_Lite_Troubleshooting.md`
  - `docs/Legacy_Ubuntu20_Scan.md`
  - `docs/Tomorrow_Final_TODO_2026-05-28.md`
  - `docs/Next_Work_Day_Report_2026-06-18.md`

## Last Verified Pi OS Lite State

- New Pi OS Lite host was using `casy@192.168.1.126`.
- ROS master was expected on the OptiTrack PC at `192.168.1.154:11311`.
- The Pi was a ROS node host, not the ROS master.
- All four services had been enabled and active:
  - `casy-mavproxy.service`
  - `casy-ros-bridges.service`
  - `casy-tracker-pipeline.service`
  - `casy-ch8-shutdown.service`
- `deploy/pi_os_lite/preflight.sh` passed.
- MAVProxy detected the flight controller on `/dev/serial0` at `921600`.
- FC state during the last automated check:
  - disarmed
  - `ALT_HOLD`
  - about `24.6 V`
  - about `98%` battery
  - zero MAVLink communication errors
- `/target_bearing` published at about `52 Hz` after stale ROS master registration cleanup.
- `/autonomy_enable` published `False`.
- `/quad_commands` had `/ros_rc_bridge` subscribed.
- A safe all-zero `/quad_commands` publish completed, and the FC remained disarmed.
- CH7 autonomy switch and CH8 shutdown behavior had previously been physically validated.
- Pi deploy scripts are now tracked executable in git to avoid chmod-only dirty state on the Pi.

## Work Added After The May Validation

- A separate Simulink ROS-device Docker target exists for the Simulink GUI workflow:
  - SSH port `2222`
  - container username `ubuntu`
  - ROS Noetic at `/opt/ros/noetic`
  - catkin workspace at `/home/ubuntu/catkin_ws`
  - compatibility symlink at `/home/user/catkin_ws`
- Simulink GUI `Test` succeeded against `192.168.1.126:2222` with the ROS folder and catkin workspace above.
- The Simulink ROS-device container is manual-start only; it is not configured to auto-start on boot.
- Latency diagnostics were added for the native tracker -> Docker ROS publisher path:
  - optional `/target_latency` topic
  - `src/ros_nodes/latency_monitor.py`
  - `tracker_to_docker_ms`, `docker_to_publish_ms`, and `tracker_to_publish_ms`
- `/target_bearing` disappearance was debugged and fixed:
  - first issue: ROS master unreachable
  - second issue: `casy-tracker-pipeline.service` restart-looped because the wrapper passed obsolete `--method scored`
  - fix: remove obsolete `--method` and `TRACKER_METHOD`; tracker is scored internally now
- The current tracker/tuning work from the other agent session is already on `origin/feat/ros-docker`.

## Open Items

1. Fix ball recognition quality.
   - Last report said the tracker recognized the target only when the ball was almost touching the lens.
   - Treat this as a vision/tuning regression or mismatch, not a ROS topic failure.
   - Reproduce with the live camera stream and current `config/green_tracker.json`.
2. Verify tracker output after recognition is fixed.
   - Confirm `/target_bearing.z` becomes `1.0` when the ball is detected.
   - Confirm yaw/pitch are valid only when calibration matches the active camera mode.
3. Power the Pi/drone with props removed and re-run the service/topic checks.
4. Confirm the OptiTrack PC is running `roscore` and publishing OptiTrack topics.
5. Verify the remote ROS graph includes:
   - `/target_bearing`
   - `/autonomy_enable`
   - `/quad_commands`
   - OptiTrack topics
6. Run tracker latency diagnostics after detection quality is restored.
7. Deploy a tiny non-flight Simulink ROS model through the ROS-device container and verify Monitor & Tune.
8. Prepare generated guidance model validation in ROS-only mode before reconnecting MAVLink command delivery.
9. Determine and mechanically lock the camera mount angle before final calibration or flight validation.
10. Keep propellers removed during MAVLink, RC override, and shutdown validation.
11. Keep red balloon and full-resolution tracking as the final roadmap task after the migrated flight stack is stable.

## Known Cautions

- If OptiTrack topics are missing but `192.168.1.154:11311` is reachable, the ROS master is probably up but the OptiTrack publisher stack is not.
- If `/target_bearing` reports `z: 0.0`, confirm the target is actually visible and the tracker tuning is sane before treating ROS publication as broken.
- Do not auto-start Simulink-generated nodes until the generated guidance package is validated.
- Stop command delivery before testing any generated model that can publish `quad_commands`: `sudo systemctl stop casy-ros-bridges.service`.
- Treat unexpected ARM/DISARM or radio failsafe messages as safety-relevant unless they are known deliberate transmitter actions.
