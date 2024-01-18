#pragma once
#include "../include/raylib.h"
#include <vector>

namespace structures {
class GameStructures {
public:
  static GameStructures &getInstance();

  GameStructures(const GameStructures &) = delete;
  void operator=(const GameStructures &) = delete;

  void addUpgradeStation(Rectangle &upgradeStation);

  Rectangle getUpgradeStation(int index) const;

private:
  GameStructures() {}

  ~GameStructures() {}

  std::vector<Rectangle> upgradeStations;
};
} // namespace structures
