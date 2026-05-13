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
    from vision_tracker.tracker import ScoringConfig, TargetTracker, TrackerConfig, score_candidates, shading_score


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
            color_fill_enabled=False,
            circularity_enabled=False,
            circle_fit_enabled=False,
            enclosing_fill_enabled=False,
            solidity_enabled=False,
            relative_area_enabled=True,
            relative_area_weight=1.0,
            shading_enabled=False,
        )
        candidates = score_candidates(mask, config, scoring)

        self.assertEqual(candidates[0].relative_area, 1.0)
        self.assertLess(candidates[1].relative_area, 1.0)
        self.assertGreater(candidates[0].area, candidates[1].area)

    def test_circle_fit_scores_circle_higher_than_elongated_blob(self):
        circle_mask = np.zeros((180, 180), dtype=np.uint8)
        elongated_mask = np.zeros((180, 180), dtype=np.uint8)
        cv2.circle(circle_mask, (90, 90), 28, 255, thickness=-1)
        cv2.ellipse(elongated_mask, (90, 90), (50, 15), 0, 0, 360, 255, thickness=-1)

        config = TrackerConfig(min_area=20, min_circularity=0.0, smoothing_alpha=1.0)
        scoring = ScoringConfig(
            min_score=0.0,
            color_fill_enabled=False,
            circularity_enabled=False,
            circle_fit_enabled=True,
            circle_fit_weight=1.0,
            enclosing_fill_enabled=False,
            solidity_enabled=False,
            relative_area_enabled=False,
            shading_enabled=False,
        )

        circle = score_candidates(circle_mask, config, scoring)[0]
        elongated = score_candidates(elongated_mask, config, scoring)[0]

        self.assertGreater(circle.circle_fit, elongated.circle_fit)
        self.assertGreater(circle.score, elongated.score)

    def test_disabled_component_does_not_affect_weighted_score(self):
        mask = np.zeros((160, 160), dtype=np.uint8)
        cv2.circle(mask, (80, 80), 28, 255, thickness=-1)

        config = TrackerConfig(min_area=20, min_circularity=0.0, smoothing_alpha=1.0)
        scoring = ScoringConfig(
            min_score=0.0,
            color_fill_enabled=True,
            color_fill_weight=1.0,
            circularity_enabled=False,
            circularity_weight=0.0,
            circle_fit_enabled=False,
            enclosing_fill_weight=0.0,
            enclosing_fill_enabled=False,
            solidity_weight=0.0,
            solidity_enabled=False,
            relative_area_enabled=False,
            shading_enabled=False,
        )
        candidates = score_candidates(mask, config, scoring)

        self.assertIsNone(candidates[0].circularity)
        self.assertIsNone(candidates[0].circle_fit)
        self.assertEqual(candidates[0].score, candidates[0].color_fill)

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

    def test_all_disabled_scoring_returns_no_detection(self):
        mask = np.zeros((120, 120), dtype=np.uint8)
        cv2.circle(mask, (60, 60), 20, 255, thickness=-1)

        tracker = TargetTracker(
            TrackerConfig(min_area=20, min_circularity=0.0, smoothing_alpha=1.0),
            ScoringConfig(
                min_score=0.0,
                color_fill_enabled=False,
                circularity_enabled=False,
                circle_fit_enabled=False,
                enclosing_fill_enabled=False,
                solidity_enabled=False,
                relative_area_enabled=False,
                shading_enabled=False,
            ),
        )

        result = tracker.update_scored(mask, image_size=type("ImageSize", (), {"width": 120, "height": 120})())

        self.assertFalse(result.detected)
        self.assertEqual(result.candidates, ())


if __name__ == "__main__":
    unittest.main()
