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
        self.assertIn("TRACKER_WIDTH=1280", text)
        self.assertIn("TRACKER_HEIGHT=720", text)
        self.assertIn("TRACKER_RAW_WIDTH=2304", text)
        self.assertIn("TRACKER_RAW_HEIGHT=1296", text)

    def test_mavproxy_service_starts_native_uart_bridge_and_stops_quickly(self):
        text = (DEPLOY_DIR / "systemd" / "casy-mavproxy.service").read_text(encoding="utf-8")

        self.assertIn("Description=CASY MAVProxy Companion Link", text)
        self.assertIn("EnvironmentFile=/etc/casy-drone/pi_os_lite.env", text)
        self.assertIn("ExecStart=/bin/bash -lc 'cd \"$PROJECT_DIR\" && exec deploy/pi_os_lite/run_mavproxy.sh'", text)
        self.assertIn("TimeoutStopSec=5", text)
        self.assertIn("KillSignal=SIGINT", text)
        self.assertIn("KillMode=control-group", text)

    def test_docker_compose_uses_remote_ros_master_for_default_services(self):
        text = (PROJECT_ROOT / "docker-compose.yml").read_text(encoding="utf-8")

        self.assertIn("ROS_MASTER_URI: ${ROS_MASTER_URI:-http://192.168.1.154:11311}", text)
        self.assertIn("ROS_IP: ${ROS_IP:-192.168.1.168}", text)
        self.assertIn("target-bearing:", text)
        self.assertIn("rc-override:", text)
        self.assertIn("rc-ch7:", text)
        self.assertIn("profiles: [\"bench\"]", text)

    def test_dockerfile_uses_apt_lxml_and_no_deps_pymavlink_install(self):
        text = (PROJECT_ROOT / "Dockerfile.ros").read_text(encoding="utf-8")

        self.assertIn("python3-lxml", text)
        self.assertIn("python3-future", text)
        self.assertIn("python3-serial", text)
        self.assertIn("pip3 install --no-cache-dir --no-deps pymavlink==2.4.49", text)

    def test_ros_exec_can_use_remote_master_without_local_roscore_container(self):
        text = (PROJECT_ROOT / "scripts" / "ros_exec.sh").read_text(encoding="utf-8")

        self.assertIn("ENV_FILE=${ENV_FILE:-/etc/casy-drone/pi_os_lite.env}", text)
        self.assertIn("docker run --rm -it --network host", text)
        self.assertIn("--env-file \"$ENV_FILE\"", text)

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
