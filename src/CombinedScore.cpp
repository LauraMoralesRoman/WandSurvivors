#include "CombinedScore.hpp"

int CombinedScore::calculatePoints(int timeSurvived, int enemiesKilled) {
  return timeSurvived * 50 + enemiesKilled * 3;
}
