#pragma once

#include "PointsStrategy.hpp"
#include <memory>
class PointSystem {
public:
  PointSystem(std::shared_ptr<PointsStrategy> strategy)
      : pointsStrategy(strategy) {}

  void setScoreStrategy(std::shared_ptr<PointsStrategy> strategy);

  int calculateScore(int timeSurvived, int enemiesKilled);

private:
  std::shared_ptr<PointsStrategy> pointsStrategy;
};
