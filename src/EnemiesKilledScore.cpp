#include "EnemiesKilledScore.hpp"

int EnemiesKilledScore::calculatePoints(int timeSurvived, int enemiesKilled) {
  return enemiesKilled * 3;
}
