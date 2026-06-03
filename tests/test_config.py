import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

try:
    import cv2  # noqa: F401
except ImportError:
    cv2 = None


if cv2 is not None:
    from vision_tracker.config import app_config_from_dict


@unittest.skipIf(cv2 is None, "OpenCV is not installed")
class ConfigTests(unittest.TestCase):
    def test_default_camera_uses_wide_camera_module_3_video_mode(self):
        config = app_config_from_dict({})

        self.assertEqual(config.camera.width, 1280)
        self.assertEqual(config.camera.height, 720)
        self.assertEqual(config.camera.raw_width, 2304)
        self.assertEqual(config.camera.raw_height, 1296)
        self.assertIsNone(config.camera.framerate)

    def test_old_scoring_config_loads_component_defaults(self):
        config = app_config_from_dict(
            {
                "scoring": {
                    "min_score": 0.5,
                    "color_fill_weight": 0.35,
                    "circularity_weight": 0.25,
                    "enclosing_fill_weight": 0.2,
                    "solidity_weight": 0.15,
                    "shading_enabled": False,
                }
            }
        )

        self.assertTrue(config.scoring.color_fill_enabled)
        self.assertTrue(config.scoring.circle_fit_enabled)
        self.assertTrue(config.scoring.relative_area_enabled)
        self.assertFalse(config.scoring.shading_enabled)

    def test_scoring_enable_flags_load_from_config(self):
        config = app_config_from_dict(
            {
                "scoring": {
                    "color_fill_enabled": False,
                    "circularity_enabled": False,
                    "circle_fit_enabled": True,
                    "enclosing_fill_enabled": False,
                    "solidity_enabled": True,
                    "relative_area_enabled": True,
                    "shading_enabled": False,
                }
            }
        )

        self.assertFalse(config.scoring.color_fill_enabled)
        self.assertFalse(config.scoring.circularity_enabled)
        self.assertTrue(config.scoring.circle_fit_enabled)
        self.assertFalse(config.scoring.enclosing_fill_enabled)
        self.assertTrue(config.scoring.solidity_enabled)
        self.assertTrue(config.scoring.relative_area_enabled)

    def test_camera_raw_size_loads_from_config(self):
        config = app_config_from_dict(
            {
                "camera": {
                    "width": 1280,
                    "height": 720,
                    "raw_width": 2304,
                    "raw_height": 1296,
                }
            }
        )

        self.assertEqual(config.camera.width, 1280)
        self.assertEqual(config.camera.height, 720)
        self.assertEqual(config.camera.raw_width, 2304)
        self.assertEqual(config.camera.raw_height, 1296)

    def test_camera_size_override_does_not_imply_raw_mode(self):
        config = app_config_from_dict(
            {
                "camera": {
                    "width": 640,
                    "height": 480,
                }
            }
        )

        self.assertEqual(config.camera.width, 640)
        self.assertEqual(config.camera.height, 480)
        self.assertIsNone(config.camera.raw_width)
        self.assertIsNone(config.camera.raw_height)

    def test_camera_framerate_loads_from_config(self):
        config = app_config_from_dict(
            {
                "camera": {
                    "framerate": 120,
                }
            }
        )

        self.assertEqual(config.camera.framerate, 120.0)


if __name__ == "__main__":
    unittest.main()
