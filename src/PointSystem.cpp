#include "PointSystem.hpp"

void PointSystem::setScoreStrategy(std::shared_ptr<PointsStrategy> strategy) {
  pointsStrategy = strategy;
}

int PointSystem::calculateScore(int timeSurvived, int enemiesKilled) {
  return pointsStrategy->calculatePoints(timeSurvived, enemiesKilled);
}
