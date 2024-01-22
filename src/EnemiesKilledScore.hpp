#pragma once

#include "PointsStrategy.hpp"
class EnemiesKilledScore : public virtual PointsStrategy {
public:
  int calculatePoints(int timeSurvived, int enemiesKilled) override;
};
