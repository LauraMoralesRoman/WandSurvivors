#pragma once

class PointsStrategy {
public:
  virtual int calculatePoints(int timeSurvived, int enemiesKilled) = 0;
  virtual ~PointsStrategy() = default;
};
