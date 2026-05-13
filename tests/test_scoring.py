import sys
import unittest
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parents[1]
SRC_DIR = PROJECT_ROOT / "src"
if str(SRC_DIR) not in sys.path:
    sys.path.insert(0, str(SRC_DIR))

try:
    import cv2
    import numpy as np
except ImportError:
    cv2 = None
    np = None

if cv2 is not None:
    from vision_tracker.tracker import ScoringConfig, TrackerConfig, score_candidates, shading_score


@unittest.skipIf(cv2 is None, "OpenCV is not installed")
class ScoringTests(unittest.TestCase):
    def test_filled_circle_scores_higher_than_thin_ring(self):
        circle_mask = np.zeros((160, 160), dtype=np.uint8)
        ring_mask = np.zeros((160, 160), dtype=np.uint8)
        cv2.circle(circle_mask, (80, 80), 28, 255, thickness=-1)
        cv2.circle(ring_mask, (80, 80), 28, 255, thickness=3)

        config = TrackerConfig(min_area=20, min_circularity=0.0, smoothing_alpha=1.0)
        scoring = ScoringConfig(min_score=0.0)

        circle = score_candidates(circle_mask, config, scoring)[0]
        ring = score_candidates(ring_mask, config, scoring)[0]

        self.assertGreater(circle.score, ring.score)
        self.assertGreater(circle.color_fill, ring.color_fill)

    def test_larger_ball_wins_score_tie_over_small_compact_noise(self):
        mask = np.zeros((220, 220), dtype=np.uint8)
        cv2.circle(mask, (45, 45), 5, 255, thickness=-1)
        cv2.circle(mask, (150, 150), 26, 255, thickness=-1)

        config = TrackerConfig(min_area=20, min_circularity=0.0, smoothing_alpha=1.0)
        scoring = ScoringConfig(
            min_score=0.0,
            color_fill_weight=1.0,
            circularity_weight=0.0,
            enclosing_fill_weight=0.0,
            solidity_weight=0.0,
        )
        candidates = score_candidates(mask, config, scoring)

        self.assertGreater(candidates[0].area, candidates[1].area)

    def test_shading_score_is_neutral_for_small_areas(self):
        frame = np.zeros((80, 80, 3), dtype=np.uint8)
        contour = np.array([[[30, 30]], [[35, 30]], [[35, 35]], [[30, 35]]])

        score = shading_score(
            frame,
            contour,
            area=25.0,
            config=ScoringConfig(shading_enabled=True, shading_min_area=400.0),
        )

        self.assertEqual(score, 0.5)

    def test_disabling_shading_removes_shading_from_weighted_score(self):
        mask = np.zeros((160, 160), dtype=np.uint8)
        frame = np.zeros((160, 160, 3), dtype=np.uint8)
        cv2.circle(mask, (80, 80), 28, 255, thickness=-1)

        tracker_config = TrackerConfig(min_area=20, min_circularity=0.0, smoothing_alpha=1.0)
        with_shading_weight_off = ScoringConfig(min_score=0.0, shading_enabled=False, shading_weight=1.0)
        without_shading_weight = ScoringConfig(min_score=0.0, shading_enabled=False, shading_weight=0.0)

        candidate_a = score_candidates(mask, tracker_config, with_shading_weight_off, frame)[0]
        candidate_b = score_candidates(mask, tracker_config, without_shading_weight, frame)[0]

        self.assertAlmostEqual(candidate_a.score, candidate_b.score)


if __name__ == "__main__":
    unittest.main()
