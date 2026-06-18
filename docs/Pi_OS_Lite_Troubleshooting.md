# Pi OS Lite Migration Troubleshooting Log

This file records the migration/debugging path from the old Ubuntu 20.04 Raspberry Pi image to the new Raspberry Pi OS Lite + ROS Docker deployment.

Keep secrets, SD-card image backup locations, and Wi-Fi passwords out of this repo.

## Active Network Assumptions

```text
Ubuntu OptiTrack ROS master: 192.168.1.154:11311
New Pi OS Lite host:        casy@192.168.1.126 during latest testing
Original planned Pi IP:     192.168.1.168
Old Ubuntu 20.04 Pi scan:   ubuntu@192.168.1.167
Ground MAVLink consumer:    192.168.1.115:14550
```

`/etc/casy-drone/pi_os_lite.env` on the Pi is the runtime source of truth for `ROS_IP`, UART, tracker, and MAVLink settings. The committed file `deploy/pi_os_lite/pi_os_lite.env.example` is only a template.

## Ubuntu 20.04 Camera Dead End

The original goal was to keep using the Ubuntu 20.04 Server Pi image, but Camera Module 3 was not usable there.

Evidence gathered on the old Ubuntu 20.04 Pi:

```text
kernel: Linux 5.4.0-1129-raspi
/boot/firmware/overlays/imx708.dtbo: missing
modinfo imx708: no imx708 kernel module
v4l2-ctl --list-devices: bcm2835-codec and bcm2835-isp only
/dev/video0: missing
dmesg: no imx708/unicam/csi camera detection
```

Package attempts did not solve the missing kernel/camera-stack support:

```text
apt install libcamera-apps: unable to locate package
apt install rpicam-apps: unable to locate package
media-ctl package: no installation candidate, but /usr/bin/media-ctl was already present
```

Conclusion: the 20.04 image remains useful as a migration reference, but not as the Camera Module 3 host OS. The camera path moved to Raspberry Pi OS Lite, where `rpicam-apps`, Picamera2, and the IMX708 stack are available.

## Headless Display Behavior

`rpicam-hello --timeout 2000` can show a preview when a real display session is available on the Pi, and it normally exits after the timeout.

OpenCV/Qt windows fail on a headless SSH-only session. The calibration attempt failed with:

```text
qt.qpa.xcb: could not connect to display
Could not load the Qt platform plugin "xcb"
```

Use one of these instead:

- run calibration/tuning through the tracker `--stream-port` support and view it from Windows with `scripts/remote_viewer.py`
- use X11 forwarding if a Windows X server is installed
- run with a real display attached to the Pi

## Legacy Image Capture

The old Ubuntu 20.04 behavior was scanned and copied into `legacy_ubuntu20_image/`.

Important findings:

- `mavproxy.service` bridged FC UART `/dev/ttyS0` at `921600` baud into local UDP MAVLink ports and `udp:192.168.1.115:14550`.
- `rc_override.service` mapped ROS `quad_commands` into MAVLink RC override.
- `ros_rc_ch7_read.service` published RC channel 7 as `autonomy_enable`.
- `ch8-shutdown.service` shut the Pi down after RC channel 8 stayed high for 1 second.
- Simulink-generated catkin packages lived under `/home/ubuntu/catkin_ws/src`.

The old shutdown delay message, `A stop job is running for MAVProxy Companion Link (UART)`, was systemd waiting for MAVProxy to stop. The old unit had no explicit short stop timeout, so systemd used its long default. The new unit sets `TimeoutStopSec=5`.

## Docker And ROS Preflight

The `casy` user must be in the `docker` group for manual Docker commands:

```bash
sudo usermod -aG docker casy
```

Log out and back in before testing `docker ps`.

`deploy/pi_os_lite/preflight.sh` checks:

- `rpicam-hello`
- Picamera2 import
- `/dev/serial0`
- Docker access
- `ROS_MASTER_URI` port reachability

If `ping 192.168.1.154` works but preflight reports connection refused on `192.168.1.154:11311`, the network is reachable but `roscore` is not listening on the Ubuntu OptiTrack PC yet.

## Git Pull Conflict On The Pi

The Pi had a local edit to `deploy/pi_os_lite/install.sh`, so `git pull` refused to overwrite it.

If the local Pi edit is disposable, discard that file and pull:

```bash
git restore deploy/pi_os_lite/install.sh
git pull
```

Only use a broader reset when every local change on the Pi is known to be disposable.

## MAVProxy Install Problems

The Pi install hit intermittent PyPI download failures while fetching `MAVProxy-1.8.74`:

```text
ProtocolError: Connection broken: IncompleteRead(...)
```

The installer now retries the full MAVProxy install up to five times and uses pip network retries/timeouts.

Runtime dependency fixes found during testing:

```text
ModuleNotFoundError: No module named 'future'
```

Fix: install `future` into `/opt/casy-drone/mavproxy-venv`.

```text
ModuleNotFoundError: No module named 'pkg_resources'
```

Fix: pin `setuptools<81` in the MAVProxy venv. Newer setuptools releases can install successfully but no longer provide the legacy runtime module MAVProxy expects.

Verification command:

```bash
/opt/casy-drone/mavproxy-venv/bin/mavproxy.py --version
```

Expected result:

```text
MAVProxy Version: 1.8.74
```

A `pkg_resources is deprecated` warning is acceptable.

## FC UART / MAVProxy Debugging

Latest test date: 2026-05-27.

Initial symptom before the FC was powered:

```text
Connect /dev/serial0 source_system=255
Waiting for heartbeat from /dev/serial0
link 1 down
```

This meant the Pi could open `/dev/serial0`, but no MAVLink heartbeat was arriving yet.

After the FC was powered over USB-C and the service was restarted, the symptom changed:

```text
Failed to connect to /dev/serial0 : [Errno 13] Permission denied
```

Root cause evidence:

```text
serial-getty@ttyS0.service: active
/boot/firmware/cmdline.txt contained console=serial0,115200
/dev/serial0 -> ttyS0
/dev/ttyS0 was crw------- root tty
ps showed /bin/login attached to ttyS0
```

The Pi serial login console was still occupying the same UART pins needed for MAVLink.

Fix applied on the Pi:

```bash
sudo systemctl stop casy-mavproxy.service
sudo systemctl disable --now serial-getty@ttyS0.service
sudo cp /boot/firmware/cmdline.txt /boot/firmware/cmdline.txt.bak-casy-serial-console
sudo sed -i 's/console=serial0,115200[[:space:]]*//' /boot/firmware/cmdline.txt
sudo chgrp dialout /dev/ttyS0
sudo chmod 660 /dev/ttyS0
sudo systemctl restart casy-mavproxy.service
```

Verify after reboot:

```bash
systemctl is-active serial-getty@ttyS0.service
cat /boot/firmware/cmdline.txt
ls -l /dev/serial0 /dev/ttyS0
journalctl -u casy-mavproxy.service -n 50 --no-pager
```

Expected:

- `serial-getty@ttyS0.service` is not active
- `cmdline.txt` does not contain `console=serial0,115200`
- `casy` has permission to open the serial device, usually through the `dialout` group
- MAVProxy receives a heartbeat

Successful verification output:

```text
Waiting for heartbeat from /dev/serial0
Detected vehicle 1:1 on link 0
online system 1
STABILIZE> Mode STABILIZE
AP: ArduCopter V4.6.3
AP: KakuteH7
Received 1251 parameters
```

Non-blocking notes from the same run:

- `Failed to load module: No module named 'adsb'` is an optional MAVProxy module warning, not the UART blocker.
- `PreArm: Battery 1 low voltage failsafe` is expected when the FC is USB-powered without the flight battery/ESC power path.
- Keep propellers removed during MAVLink and RC override validation.
- `casy-mavproxy.service` was intentionally left disabled for boot while validation continues.

## Next Troubleshooting Targets

After UART is stable:

1. Test CH8 shutdown through `casy-ch8-shutdown.service`.
2. Start Docker ROS bridge services and verify `autonomy_enable` changes with RC channel 7.
3. Publish a safe `quad_commands` message containing zeros and confirm the RC override bridge sends MAVLink ignore values, not active overrides.
4. Start the tracker pipeline and verify `/target_bearing` on the remote ROS master.
5. Only then enable services for boot.

## MAVProxy UDP Consumer Contention

Latest test date: 2026-05-27.

Symptom:

```text
/autonomy_enable existed on the remote ROS master and had publisher /rc_ch7_enable,
but rostopic echo -n 1 /autonomy_enable produced no sample.
rc-ch7 logs showed heartbeat received, but never logged Autonomy ENABLED/DISABLED.
```

Evidence:

```text
/target_bearing published normally at about 39 Hz.
MAVProxy was active and receiving FC messages.
A separate pymavlink probe connected to udp:127.0.0.1:14552 saw RC_CHANNELS at about 4 Hz.
RC_CHANNELS included chan7_raw=982 and chan8_raw=982.
```

Root cause:

```text
Multiple local MAVLink consumers were configured to use the same MAVProxy UDP output, 127.0.0.1:14552:
  rc-ch7
  rc-override
  CH8 shutdown listener
  ad-hoc diagnostic probes
```

That is not a reliable broadcast pattern. Even when several processes can bind/connect, a single local UDP stream should not be treated as shared fan-out for independent consumers.

Fix:

```text
MAVLINK_OUT_LOCAL_1=udp:127.0.0.1:14551 -> RC CH7 autonomy_enable
MAVLINK_OUT_LOCAL_2=udp:127.0.0.1:14552 -> quad_commands RC override
MAVLINK_OUT_LOCAL_3=udp:127.0.0.1:14553 -> CH8 shutdown listener
```

Repo changes:

```text
docker-compose.yml sets MAVLINK_RC_CH7_ENDPOINT and MAVLINK_RC_OVERRIDE_ENDPOINT separately.
ros_rc_ch7_read.py reads MAVLINK_RC_CH7_ENDPOINT first.
ros_rc_bridge.py reads MAVLINK_RC_OVERRIDE_ENDPOINT first.
deploy/pi_os_lite/pi_os_lite.env.example assigns CH8 shutdown to port 14553.
```

After pulling these changes on an already-installed Pi, manually update `/etc/casy-drone/pi_os_lite.env` to match the split ports because `install.sh` does not overwrite an existing env file.

Verification:

```text
After rebuilding/recreating the bridge containers, rc-ch7 connected to udp:127.0.0.1:14551.
The node logged Autonomy DISABLED (CH7 = 982).
Flipping the actual transmitter switch logged Autonomy ENABLED (CH7 = 2006), then Autonomy DISABLED (CH7 = 982).
rostopic echo -n 1 /autonomy_enable returned data: False after returning the switch low.
```

## CH8 Shutdown Script Python Environment

Latest test date: 2026-05-27.

Symptom while running a non-destructive CH8 dry-run test:

```text
ModuleNotFoundError: No module named 'pymavlink'
```

Root cause:

```text
deploy/pi_os_lite/shutdown_on_ch8.py imports pymavlink.
install.sh installs pymavlink into /opt/casy-drone/mavproxy-venv, not into the system Python.
The original systemd unit used /usr/bin/python3.
```

Fix:

```text
casy-ch8-shutdown.service now runs:
/opt/casy-drone/mavproxy-venv/bin/python deploy/pi_os_lite/shutdown_on_ch8.py
```

Dry-run test command:

```bash
MAVLINK_SHUTDOWN_PORT=14553 \
SHUTDOWN_SUDO='' \
SHUTDOWN_COMMAND='/bin/echo ch8-shutdown-dry-run' \
timeout 25 \
/opt/casy-drone/mavproxy-venv/bin/python deploy/pi_os_lite/shutdown_on_ch8.py
```

If `SHUTDOWN_SUDO` is not set, the script prepends `sudo`, which is the intended production behavior.

Verification:

```text
Synthetic MAVLink CH8 low-to-high input triggered the dry-run command and printed ch8-shutdown-dry-run.
The actual FC CH8 switch also triggered the dry-run command and printed ch8-shutdown-dry-run.
```

## Post-Reboot Service Validation

Latest test date: 2026-05-28.

The Pi repo initially looked dirty after yesterday's install work:

```text
M deploy/pi_os_lite/install.sh
M deploy/pi_os_lite/preflight.sh
M deploy/pi_os_lite/run_mavproxy.sh
M deploy/pi_os_lite/run_tracker_pipeline.sh
M deploy/pi_os_lite/shutdown_on_ch8.py
```

`git diff --stat` showed `0 insertions, 0 deletions`, and the files were executable on the Pi while the repo tracked them as `100644`. Root cause: install-time `chmod +x` created mode-only changes. Fix: the deploy entrypoints are now tracked as executable (`100755`) in git. After restoring the old local mode noise and pulling the new commit, the Pi repo was clean and the scripts remained executable.

Post-reboot checks passed:

```text
systemctl is-enabled:
  casy-mavproxy.service          enabled
  casy-ros-bridges.service       enabled
  casy-tracker-pipeline.service  enabled
  casy-ch8-shutdown.service      enabled

systemctl is-active:
  all four services active

deploy/pi_os_lite/preflight.sh:
  rpicam-hello found
  Picamera2 import ok
  /dev/serial0 -> ttyS0
  Docker access ok
  ROS master port 192.168.1.154:11311 reachable
```

MAVProxy/FC verification through the TCP MAVLink output:

```text
heartbeat system=1 component=0 armed=False mode=ALT_HOLD
voltage_battery: 24594 mV
battery_remaining: 98
drop_rate_comm: 0
errors_comm: 0
```

MAVProxy logs also showed brief radio failsafe messages and an ARM/DISARM event during bench testing. Treat these as safety-relevant if they are not caused by deliberate transmitter actions. Props remained removed.

ROS graph verification:

```text
/autonomy_enable
/quad_commands
/target_bearing
```

`/quad_commands` had `/ros_rc_bridge` subscribed. A safe all-zero `std_msgs/UInt16MultiArray` was published to `/quad_commands` from a temporary container-side `rospy` script. The RC bridge stayed running, and the FC remained disarmed afterward.

`/target_bearing` was publishing at about 52 Hz. One stale `/target_bearing` publisher remained registered in the remote ROS master after an older container exited:

```text
/target_bearing_publisher_1_1779895707575 -> contact failed
```

Root cause: stale ROS master registration, not a second live tracker pipeline. `rosnode cleanup` removed it. After cleanup, `/target_bearing` had one live publisher.

Remaining blockers from this validation pass:

- OptiTrack topics were not present on the remote ROS master during the check, even though the master was reachable.
- `/target_bearing` sampled `z: 0.0` during the automated check because no visible target was confirmed at that moment.
- The active Simulink-generated package is still not identified. `test_position_control4` is the newest/largest-looking candidate, but that is not proof. Do not auto-start any generated node until the intended package is confirmed.

## Simulink ROS Device Container

Latest planning date: 2026-06-18.

Goal:

```text
Preserve the old Simulink GUI workflow where Simulink deploys a ROS package over SSH,
starts it on the target, and monitors model outputs from the Simulink model.
```

Implementation approach:

```text
Dockerfile.simulink-ros-device builds a separate ROS Noetic SSH target.
docker compose service simulink-ros-device uses network_mode: host.
container sshd listens on port 2222.
container user is ubuntu.
ROS folder is /opt/ros/noetic.
catkin workspace is /home/ubuntu/catkin_ws.
/home/user/catkin_ws is a compatibility alias for Simulink probes.
default host workspace mount is /home/casy/simulink_catkin_ws.
password source is /etc/casy-drone/simulink_ros_device_password.
```

The password file is local to the Pi and must stay out of git:

```bash
deploy/pi_os_lite/simulink_ros_device.sh init-password
```

Build/start/check commands:

```bash
deploy/pi_os_lite/simulink_ros_device.sh build
deploy/pi_os_lite/simulink_ros_device.sh start
deploy/pi_os_lite/simulink_ros_device.sh check
```

Windows SSH smoke test:

```powershell
ssh -p 2222 ubuntu@192.168.1.126 "source /opt/ros/noetic/setup.bash && rosversion -d"
```

Simulink GUI settings to test:

```text
Device address: 192.168.1.126:2222
Username: ubuntu
ROS folder: /opt/ros/noetic
Catkin workspace: /home/ubuntu/catkin_ws
```

Important experiment boundary:

```text
The Simulink GUI Test button successfully connected to 192.168.1.126:2222.
Do not add SSH aliases, host forwarding, native ROS installs, or other
fallback plumbing for the port unless a later deployment step proves it is needed.
```

Safety boundary for guidance-node tests:

```bash
sudo systemctl stop casy-ros-bridges.service
```

Do this before deploying a generated model that can publish `quad_commands`, so ROS-only behavior can be verified before MAVLink command delivery is reconnected. Props remain removed for any MAVLink/RC override validation.

Pi build/smoke verification on 2026-06-18:

```text
Pi checkout fast-forwarded cleanly to feat/ros-docker commit 0a34fb4.
deploy/pi_os_lite/simulink_ros_device.sh build completed successfully.
Built image: casy-simulink-ros-device:latest.
Temporary password-file smoke test started the container with a temporary workspace.
Inside the container, rosversion -d returned noetic.
Inside the container, catkin_make completed successfully in /home/ubuntu/catkin_ws.
The temporary container and temporary password/workspace files were removed afterward.
Port 2222 was closed after cleanup.
```

Simulink GUI test result:

```text
Pinging 192.168.1.126 succeeded.
SSH connection to 192.168.1.126 port 2222 as ubuntu succeeded.
Simulink detected sudo privileges, with sudo requiring a password.
Simulink found ROS Noetic in /opt/ros/noetic.
Simulink then checked /home/user/catkin_ws and reported the folder missing.
```

Fix:

```text
Keep /home/ubuntu/catkin_ws as the canonical mounted workspace.
Provide /home/user/catkin_ws as a container-side symlink to the same workspace,
because Simulink may probe that path even when the SSH username is ubuntu.
```

Pending manual test:

```text
Rebuild and restart the Simulink ROS-device container after the workspace alias change.
Use the Simulink GUI Test button again with Device address 192.168.1.126:2222.
If the workspace check still points at /home/user/catkin_ws, click Fix only after
confirming the path resolves to the mounted workspace.
```
