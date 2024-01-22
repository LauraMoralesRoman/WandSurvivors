#pragma once

#include "PointsStrategy.hpp"
class CombinedScore : public virtual PointsStrategy {
public:
  int calculatePoints(int timeSurvived, int enemiesKilled) override;
};
