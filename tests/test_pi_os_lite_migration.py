import importlib.util
import sys
import unittest
from pathlib import Path


PROJECT_ROOT = Path(__file__).resolve().parents[1]
DEPLOY_DIR = PROJECT_ROOT / "deploy" / "pi_os_lite"
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))


def load_ros_node(name):
    path = PROJECT_ROOT / "src" / "ros_nodes" / f"{name}.py"
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


class PiOsLiteMigrationTests(unittest.TestCase):
    def test_env_template_locks_migration_network_and_runtime_defaults(self):
        text = (DEPLOY_DIR / "pi_os_lite.env.example").read_text(encoding="utf-8")

        self.assertIn("ROS_MASTER_URI=http://192.168.1.154:11311", text)
        self.assertIn("ROS_IP=192.168.1.168", text)
        self.assertIn("FC_UART=/dev/serial0", text)
        self.assertIn("MAVLINK_BAUD=921600", text)
        self.assertIn("MAVLINK_OUT_GROUND=udp:192.168.1.115:14550", text)
        self.assertIn("MAVLINK_RC_CH7_ENDPOINT=udp:127.0.0.1:14551", text)
        self.assertIn("MAVLINK_RC_OVERRIDE_ENDPOINT=udp:127.0.0.1:14552", text)
        self.assertIn("MAVLINK_SHUTDOWN_PORT=14553", text)
        self.assertIn("TRACKER_WIDTH=1280", text)
        self.assertIn("TRACKER_HEIGHT=720", text)
        self.assertIn("TRACKER_RAW_WIDTH=2304", text)
        self.assertIn("TRACKER_RAW_HEIGHT=1296", text)
        self.assertIn("LATENCY_DIAGNOSTICS=0", text)
        self.assertIn("TARGET_LATENCY_TOPIC=/target_latency", text)

    def test_mavproxy_service_starts_native_uart_bridge_and_stops_quickly(self):
        text = (DEPLOY_DIR / "systemd" / "casy-mavproxy.service").read_text(encoding="utf-8")

        self.assertIn("Description=CASY MAVProxy Companion Link", text)
        self.assertIn("EnvironmentFile=/etc/casy-drone/pi_os_lite.env", text)
        self.assertIn("ExecStart=/bin/bash -lc 'cd \"$PROJECT_DIR\" && exec deploy/pi_os_lite/run_mavproxy.sh'", text)
        self.assertIn("TimeoutStopSec=5", text)
        self.assertIn("KillSignal=SIGINT", text)
        self.assertIn("KillMode=control-group", text)

    def test_ch8_shutdown_service_uses_mavproxy_venv_python(self):
        text = (DEPLOY_DIR / "systemd" / "casy-ch8-shutdown.service").read_text(encoding="utf-8")

        self.assertIn("/opt/casy-drone/mavproxy-venv/bin/python deploy/pi_os_lite/shutdown_on_ch8.py", text)

    def test_ch8_shutdown_script_supports_dry_run_without_sudo(self):
        text = (DEPLOY_DIR / "shutdown_on_ch8.py").read_text(encoding="utf-8")

        self.assertIn('SUDO_COMMAND = os.getenv("SHUTDOWN_SUDO", "sudo").split()', text)
        self.assertIn("subprocess.run([*SUDO_COMMAND, *SHUTDOWN_COMMAND], check=False)", text)

    def test_docker_compose_uses_remote_ros_master_for_default_services(self):
        text = (PROJECT_ROOT / "docker-compose.yml").read_text(encoding="utf-8")

        self.assertIn("ROS_MASTER_URI: ${ROS_MASTER_URI:-http://192.168.1.154:11311}", text)
        self.assertIn("ROS_IP: ${ROS_IP:-192.168.1.168}", text)
        self.assertIn("target-bearing:", text)
        self.assertIn("rc-override:", text)
        self.assertIn("rc-ch7:", text)
        self.assertIn("MAVLINK_RC_OVERRIDE_ENDPOINT: ${MAVLINK_RC_OVERRIDE_ENDPOINT:-udp:127.0.0.1:14552}", text)
        self.assertIn("MAVLINK_RC_CH7_ENDPOINT: ${MAVLINK_RC_CH7_ENDPOINT:-udp:127.0.0.1:14551}", text)
        self.assertIn("LATENCY_DIAGNOSTICS: ${LATENCY_DIAGNOSTICS:-0}", text)
        self.assertIn("TARGET_LATENCY_TOPIC: ${TARGET_LATENCY_TOPIC:-/target_latency}", text)
        self.assertIn("profiles: [\"bench\"]", text)

    def test_simulink_ros_device_compose_service_is_isolated_and_profile_gated(self):
        text = (PROJECT_ROOT / "docker-compose.yml").read_text(encoding="utf-8")

        self.assertIn("simulink-ros-device:", text)
        self.assertIn("dockerfile: Dockerfile.simulink-ros-device", text)
        self.assertIn("image: ${SIMULINK_ROS_DEVICE_IMAGE:-casy-simulink-ros-device}", text)
        self.assertIn('network_mode: "host"', text)
        self.assertIn("SIMULINK_ROS_DEVICE_SSH_PORT: ${SIMULINK_ROS_DEVICE_SSH_PORT:-2222}", text)
        self.assertIn("SIMULINK_ROS_DEVICE_PASSWORD_FILE: /run/secrets/simulink_ros_device_password", text)
        self.assertIn("${SIMULINK_CATKIN_HOST_DIR:-/home/casy/simulink_catkin_ws}:/home/ubuntu/catkin_ws", text)
        self.assertIn("${SIMULINK_ROS_DEVICE_PASSWORD_FILE:-/etc/casy-drone/simulink_ros_device_password}:/run/secrets/simulink_ros_device_password:ro", text)
        self.assertIn('profiles: ["simulink"]', text)

    def test_dockerfile_uses_apt_lxml_and_no_deps_pymavlink_install(self):
        text = (PROJECT_ROOT / "Dockerfile.ros").read_text(encoding="utf-8")

        self.assertIn("python3-lxml", text)
        self.assertIn("python3-future", text)
        self.assertIn("python3-serial", text)
        self.assertIn("pip3 install --no-cache-dir --no-deps pymavlink==2.4.49", text)

    def test_simulink_ros_device_dockerfile_matches_simulink_remote_target(self):
        text = (PROJECT_ROOT / "Dockerfile.simulink-ros-device").read_text(encoding="utf-8")

        self.assertIn("FROM ros:noetic-ros-base-focal", text)
        self.assertIn("ENV SIMULINK_ROS_DEVICE_SSH_PORT=2222", text)
        self.assertIn("ENV SIMULINK_CATKIN_WORKSPACE=/home/ubuntu/catkin_ws", text)
        self.assertIn("openssh-server", text)
        self.assertIn("python3-catkin-tools", text)
        self.assertIn("ros-noetic-geometry-msgs", text)
        self.assertIn("ros-noetic-std-msgs", text)
        self.assertIn("useradd -m -s /bin/bash ubuntu", text)
        self.assertIn("mkdir -p /home/ubuntu/catkin_ws/src /home/user /run/sshd", text)
        self.assertIn("ln -s /home/ubuntu/catkin_ws /home/user/catkin_ws", text)
        self.assertIn("COPY docker/simulink_ros_device/entrypoint.sh", text)
        self.assertIn("EXPOSE 2222", text)

    def test_simulink_ros_device_entrypoint_requires_runtime_password(self):
        text = (PROJECT_ROOT / "docker" / "simulink_ros_device" / "entrypoint.sh").read_text(encoding="utf-8")

        self.assertIn('SSH_PORT="${SIMULINK_ROS_DEVICE_SSH_PORT:-2222}"', text)
        self.assertIn('PASSWORD_FILE="${SIMULINK_ROS_DEVICE_PASSWORD_FILE:-}"', text)
        self.assertIn("SIMULINK_ROS_DEVICE_PASSWORD or SIMULINK_ROS_DEVICE_PASSWORD_FILE is required", text)
        self.assertIn("printf 'ubuntu:%s\\n' \"$PASSWORD\" | chpasswd", text)
        self.assertIn("Port ${SSH_PORT}", text)
        self.assertIn("PasswordAuthentication yes", text)
        self.assertIn("AllowUsers ubuntu", text)
        self.assertIn("ln -s \"$WORKSPACE\" /home/user/catkin_ws", text)
        self.assertIn("exec /usr/sbin/sshd -D -e", text)

    def test_simulink_ros_device_helper_uses_local_secret_file_and_profile(self):
        text = (DEPLOY_DIR / "simulink_ros_device.sh").read_text(encoding="utf-8")

        self.assertIn('SERVICE="simulink-ros-device"', text)
        self.assertIn('PASSWORD_FILE="${SIMULINK_ROS_DEVICE_PASSWORD_FILE:-/etc/casy-drone/simulink_ros_device_password}"', text)
        self.assertIn("init-password", text)
        self.assertIn('docker compose --env-file "$ENV_FILE" --profile simulink "$@"', text)
        self.assertIn('compose build "$SERVICE"', text)
        self.assertIn('compose up -d "$SERVICE"', text)
        self.assertIn('source /opt/ros/noetic/setup.bash && rosversion -d', text)
        self.assertNotIn("SIMULINK_ROS_DEVICE_PASSWORD=", text)

    def test_env_template_includes_simulink_ros_device_defaults_without_secret(self):
        text = (DEPLOY_DIR / "pi_os_lite.env.example").read_text(encoding="utf-8")

        self.assertIn("SIMULINK_ROS_DEVICE_IMAGE=casy-simulink-ros-device", text)
        self.assertIn("SIMULINK_ROS_DEVICE_SSH_PORT=2222", text)
        self.assertIn("SIMULINK_ROS_DEVICE_PASSWORD_FILE=/etc/casy-drone/simulink_ros_device_password", text)
        self.assertIn("SIMULINK_CATKIN_HOST_DIR=/home/casy/simulink_catkin_ws", text)
        self.assertNotIn("SIMULINK_ROS_DEVICE_PASSWORD=", text)

    def test_install_script_uses_pip_retries_for_mavproxy_downloads(self):
        text = (DEPLOY_DIR / "install.sh").read_text(encoding="utf-8")

        self.assertIn("--upgrade pip 'setuptools<81'", text)
        self.assertIn("for attempt in 1 2 3 4 5", text)
        self.assertIn("pip install --retries 10 --timeout 120 MAVProxy pymavlink pyserial future", text)
        self.assertIn("MAVProxy pymavlink pyserial future", text)

    def test_ros_exec_can_use_remote_master_without_local_roscore_container(self):
        text = (PROJECT_ROOT / "scripts" / "ros_exec.sh").read_text(encoding="utf-8")

        self.assertIn("ENV_FILE=${ENV_FILE:-/etc/casy-drone/pi_os_lite.env}", text)
        self.assertIn("docker run --rm -it --network host", text)
        self.assertIn("--env-file \"$ENV_FILE\"", text)

    def test_tracker_pipeline_does_not_pass_removed_method_argument(self):
        text = (DEPLOY_DIR / "run_tracker_pipeline.sh").read_text(encoding="utf-8")

        self.assertIn("python3 scripts/green_tracker.py", text)
        self.assertIn("--output json", text)
        self.assertNotIn("--method", text)
        self.assertNotIn("TRACKER_METHOD", text)

    def test_rc_bridge_maps_simulink_quad_commands_to_mavlink_override_channels(self):
        bridge = load_ros_node("ros_rc_bridge")

        mapped = bridge.map_quad_commands([1500, 1600, 900, 2100, 1234, 1700])

        self.assertEqual(mapped, [1500, 1600, 1000, 2000, 1700])
        self.assertEqual(bridge.sanitize_pwm(0), bridge.IGNORE)
        self.assertEqual(bridge.sanitize_pwm(bridge.IGNORE), bridge.IGNORE)

    def test_rc_bridge_ignores_short_quad_command_messages(self):
        bridge = load_ros_node("ros_rc_bridge")

        self.assertIsNone(bridge.map_quad_commands([1500, 1600, 1700, 1800, 1900]))


if __name__ == "__main__":
    unittest.main()
