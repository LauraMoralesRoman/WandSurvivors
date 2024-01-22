#pragma once
#include "PointsStrategy.hpp"

class TimeSurvivedScore : public virtual PointsStrategy {
public:
  int calculatePoints(int timeSurvived, int enemiesKilled) override;
};
