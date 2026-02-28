from ultralytics.models.fastsam import FastSAMPredictor

# Create FastSAMPredictor
overrides = dict(conf=0.25, task="segment", mode="predict", model="./../model/FastSAM-s.pt", save=True, imgsz=1024)
predictor = FastSAMPredictor(overrides=overrides)

# Segment everything
everything_results = predictor("./../source/car.jpg")

# Prompt inference
bbox_results = predictor.prompt(everything_results, bboxes=[[200, 200, 300, 300]])
point_results = predictor.prompt(everything_results, points=[200, 200])