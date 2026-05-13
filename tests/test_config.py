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


if __name__ == "__main__":
    unittest.main()
