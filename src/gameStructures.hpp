#pragma once
#include "../include/raylib.h"
#include "entities/GenericEnemy.hpp"
#include "entities/Spell.hpp"
#include "entities/UpgradeShop.hpp"
#include <algorithm>
#include <memory>
#include <vector>

namespace structures {
class GameStructures {
public:
  static GameStructures &getInstance();

  GameStructures(const GameStructures &) = delete;
  void operator=(const GameStructures &) = delete;

  void addUpgradeStation(std::shared_ptr<UpgradeShop> upgradeStation);

  std::vector<std::shared_ptr<UpgradeShop>> &getUpgradeStations();

  std::vector<std::shared_ptr<GenericEnemy>> &getGenericEnemies();
  void addEnemy(GenericEnemy &enemy);
  void deleteEnemy();
  const int getMaxEnemies() const;

  std::vector<std::shared_ptr<Spell>> &getSpells();
  void addSpell(std::shared_ptr<Spell> spell);

private:
  GameStructures() {}

  ~GameStructures() {}

  std::vector<std::shared_ptr<UpgradeShop>> upgradeStations;

  std::vector<std::shared_ptr<GenericEnemy>> genericEnemies;
  const int maxEnemies = 5;

  std::vector<std::shared_ptr<Spell>> spells;
};
} // namespace structures
