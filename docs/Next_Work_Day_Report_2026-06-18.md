# Next Work Day Report - 2026-06-18

## Current Status

- Active branch: `feat/ros-docker`.
- Pi host used today: `casy@192.168.1.126`.
- Remote ROS master target: `http://192.168.1.154:11311`.
- Pi runtime env source of truth remains `/etc/casy-drone/pi_os_lite.env`.
- Core boot services are enabled:
  - `casy-mavproxy.service`
  - `casy-ch8-shutdown.service`
  - `casy-ros-bridges.service`
  - `casy-tracker-pipeline.service`
- Simulink ROS-device container exists and works for manual deploy/monitor tests, but it is not configured to auto-start on boot.

## Completed Today

- Added and validated a separate Simulink ROS-device Docker target:
  - SSH on port `2222`
  - username `ubuntu`
  - ROS Noetic at `/opt/ros/noetic`
  - catkin workspace at `/home/ubuntu/catkin_ws`
  - compatibility alias `/home/user/catkin_ws`
- Simulink GUI `Test` succeeded with:
  - `Device address: 192.168.1.126:2222`
  - `Username: ubuntu`
  - `ROS folder: /opt/ros/noetic`
  - `Catkin workspace: /home/ubuntu/catkin_ws`
- Added latency diagnostics for the native tracker -> Docker ROS publisher path:
  - `/target_latency` optional diagnostic topic
  - `latency_monitor.py` rolling summary script
  - future full-chain latency target documented
- Fixed `/target_bearing` disappearance:
  - first issue was unreachable ROS master
  - second issue was `casy-tracker-pipeline.service` restart-looping because `run_tracker_pipeline.sh` passed obsolete `--method scored`
  - removed the obsolete flag and `TRACKER_METHOD` from the env template
  - verified `/target_bearing` appears and publishes `geometry_msgs/PointStamped`
- Documented the recovery path in `docs/Pi_OS_Lite_Troubleshooting.md`.

## Known Issues

- Ball recognition is currently bad: the tracker only recognizes the target when the ball is almost touching the camera lens.
- This is a vision/tracker quality regression or tuning mismatch, not a ROS-topic publication failure.
- `/target_bearing` can publish `z: 0.0` when no valid target is detected.
- OptiTrack ROS master availability still matters: if `192.168.1.154:11311` is down, Pi ROS topics cannot register.
- The guidance Simulink model/package is not generated/deployed/validated yet.
- The Simulink ROS-device container is manual-start only for now.

## Next Work Day Priority Tasks

1. Fix ball recognition algorithm/tuning.
   - Reproduce with live camera view and current `config/green_tracker.json`.
   - Use streamed tuning if working headless:
     ```bash
     python3 scripts/tune_tracker.py --stream-port 5000
     ```
     ```powershell
     python scripts/remote_viewer.py --ip 192.168.1.126 --port 5000
     ```
   - Check whether the issue is HSV thresholds, `min_area`, scoring `min_score`, circularity gate, focus, exposure, calibration geometry, or the switch to the wider `2304x1296` raw mode.
   - Save corrected tracker config only after verifying detection at realistic distances.

2. Verify tracker output after recognition fix.
   - Confirm `/target_bearing` changes to `z: 1.0` when the ball is detected.
   - Confirm yaw/pitch are non-null only when calibration matches the active camera mode.
   - Check publish rate:
     ```bash
     docker run --rm --network host --env-file /etc/casy-drone/pi_os_lite.env casy-ros-node \
       bash -lc "source /opt/ros/noetic/setup.bash && rostopic hz /target_bearing"
     ```

3. Run latency diagnostics with the tracker active.
   - Temporarily enable:
     ```text
     LATENCY_DIAGNOSTICS=1
     TARGET_LATENCY_TOPIC=/target_latency
     ```
   - Restart tracker pipeline and monitor:
     ```bash
     ./scripts/ros_exec.sh python3 /app/src/ros_nodes/latency_monitor.py
     ```
   - Record typical `tracker_to_docker_ms`, `docker_to_publish_ms`, and `tracker_to_publish_ms`.

4. Deploy a tiny non-flight Simulink ROS model.
   - Use the working `192.168.1.126:2222` ROS-device connection.
   - Verify Simulink deploy, run, and Monitor & Tune.
   - Do not test flight commands in this first model.

5. Prepare for generated guidance model validation.
   - Stop command delivery before any model that publishes `quad_commands`:
     ```bash
     sudo systemctl stop casy-ros-bridges.service
     ```
   - Validate ROS-only behavior first:
     ```text
     subscribe /target_bearing      geometry_msgs/PointStamped
     subscribe /autonomy_enable     std_msgs/Bool
     publish   /quad_commands       std_msgs/UInt16MultiArray
     ```
   - Confirm `/quad_commands` is zero/no-override when autonomy is false or target is lost.

6. Decide whether Simulink ROS-device should auto-start on boot.
   - Keep it manual until Monitor & Tune and the generated model path are proven.
   - If approved later, add a dedicated systemd unit or compose restart policy deliberately.

7. Re-check boot behavior with props removed.
   - Power-cycle the Pi/drone system.
   - Confirm MAVProxy, CH8 shutdown, ROS bridges, and tracker pipeline start cleanly.
   - Confirm `/target_bearing`, `/autonomy_enable`, and `/quad_commands` presence on the ROS master.

## Useful Commands

```bash
cd ~/balloon_tracker
git status --short
systemctl --no-pager --full status casy-mavproxy.service
systemctl --no-pager --full status casy-ros-bridges.service
systemctl --no-pager --full status casy-tracker-pipeline.service
systemctl --no-pager --full status casy-ch8-shutdown.service
journalctl -u casy-tracker-pipeline.service -n 80 --no-pager
```

```bash
docker run --rm --network host --env-file /etc/casy-drone/pi_os_lite.env casy-ros-node \
  bash -lc "source /opt/ros/noetic/setup.bash && rostopic list"
```

```bash
docker run --rm --network host --env-file /etc/casy-drone/pi_os_lite.env casy-ros-node \
  bash -lc "source /opt/ros/noetic/setup.bash && rostopic echo -n 1 /target_bearing"
```

## Safety Notes

- Keep propellers removed for MAVLink, RC override, and generated guidance validation.
- Do not auto-start generated Simulink nodes until the active generated package is validated.
- Do not reconnect command delivery to MAVLink until ROS-only guidance behavior is verified.
