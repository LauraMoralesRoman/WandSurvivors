#include "gameStructures.hpp"

namespace structures {

GameStructures &GameStructures::getInstance() {
  static GameStructures instance;
  return instance;
}

void GameStructures::addUpgradeStation(Rectangle &upgradeStation) {
  upgradeStations.push_back(upgradeStation);
}

Rectangle GameStructures::getUpgradeStation(int index) const {
  if (index > 0 && index < upgradeStations.size()) {
    return upgradeStations[index];
  } else {
    return Rectangle{0, 0, 0, 0};
  }
}

} // namespace structures
