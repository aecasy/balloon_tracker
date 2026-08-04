import json
import sys
import unittest
from pathlib import Path


PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

from ros_nodes.latency_diagnostics import (
    RollingLatencyStats,
    build_latency_payload,
    format_latency_payload,
    is_enabled,
)


class LatencyDiagnosticsTests(unittest.TestCase):
    def test_build_latency_payload_calculates_stage_delays_ms(self):
        frame = {
            "timestamp": 100.0,
            "detected": True,
            "yaw_deg": 1.25,
            "pitch_deg": -0.5,
        }

        payload = build_latency_payload(
            frame,
            sequence=7,
            docker_receive_time=100.012,
            ros_publish_time=100.0155,
        )

        self.assertEqual(payload["sequence"], 7)
        self.assertTrue(payload["detected"])
        self.assertEqual(payload["tracker_timestamp"], 100.0)
        self.assertEqual(payload["docker_receive_time"], 100.012)
        self.assertEqual(payload["ros_publish_time"], 100.0155)
        self.assertAlmostEqual(payload["tracker_to_docker_ms"], 12.0)
        self.assertAlmostEqual(payload["docker_to_publish_ms"], 3.5)
        self.assertAlmostEqual(payload["tracker_to_publish_ms"], 15.5)

    def test_build_latency_payload_handles_missing_tracker_timestamp(self):
        payload = build_latency_payload(
            {"detected": False},
            sequence=3,
            docker_receive_time=50.0,
            ros_publish_time=50.001,
        )

        self.assertEqual(payload["sequence"], 3)
        self.assertFalse(payload["detected"])
        self.assertIsNone(payload["tracker_timestamp"])
        self.assertIsNone(payload["tracker_to_docker_ms"])
        self.assertIsNone(payload["tracker_to_publish_ms"])
        self.assertAlmostEqual(payload["docker_to_publish_ms"], 1.0)

    def test_format_latency_payload_is_compact_json(self):
        payload = {"sequence": 1, "tracker_to_publish_ms": 2.5}

        text = format_latency_payload(payload)

        self.assertEqual(json.loads(text), payload)
        self.assertNotIn(" ", text)

    def test_is_enabled_accepts_common_truthy_values(self):
        for value in ("1", "true", "TRUE", "yes", "on", "enabled"):
            with self.subTest(value=value):
                self.assertTrue(is_enabled(value))

        for value in (None, "", "0", "false", "off", "no"):
            with self.subTest(value=value):
                self.assertFalse(is_enabled(value))

    def test_rolling_latency_stats_reports_min_avg_max_and_p95(self):
        stats = RollingLatencyStats(window_size=5)
        for value in (10.0, 20.0, 30.0, 40.0, 50.0):
            stats.add({"tracker_to_publish_ms": value})

        summary = stats.summary("tracker_to_publish_ms")

        self.assertEqual(summary["count"], 5)
        self.assertEqual(summary["min"], 10.0)
        self.assertEqual(summary["avg"], 30.0)
        self.assertEqual(summary["max"], 50.0)
        self.assertEqual(summary["p95"], 50.0)

    def test_rolling_latency_stats_ignores_missing_values(self):
        stats = RollingLatencyStats(window_size=3)
        stats.add({"tracker_to_publish_ms": None})
        stats.add({"docker_to_publish_ms": 1.0})

        self.assertIsNone(stats.summary("tracker_to_publish_ms"))
        self.assertEqual(stats.summary("docker_to_publish_ms")["count"], 1)


if __name__ == "__main__":
    unittest.main()
