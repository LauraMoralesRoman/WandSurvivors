#include "gameStructures.hpp"
#include "entities/UpgradeShop.hpp"

namespace structures {

GameStructures &GameStructures::getInstance() {
  static GameStructures instance;
  return instance;
}

void GameStructures::addUpgradeStation(
    std::shared_ptr<UpgradeShop> upgradeStation) {
  upgradeStations.push_back(upgradeStation);
}

std::vector<std::shared_ptr<UpgradeShop>> &
GameStructures::getUpgradeStations() {
  return upgradeStations;
}

std::vector<std::shared_ptr<GenericEnemy>> &
GameStructures::getGenericEnemies() {
  return genericEnemies;
}

void GameStructures::addEnemy(GenericEnemy &enemy) {
  std::shared_ptr<GenericEnemy> sharedEnemy =
      std::make_shared<GenericEnemy>(enemy);
  genericEnemies.push_back(sharedEnemy);
}

void GameStructures::deleteEnemy() {

  genericEnemies.erase(
      std::remove_if(genericEnemies.begin(), genericEnemies.end(),
                     [](const std::shared_ptr<GenericEnemy> &enemy) {
                       return enemy->getStats().health <= 0.0f;
                     }),
      genericEnemies.end());
}

const int GameStructures::getMaxEnemies() const { return maxEnemies; }

std::vector<std::shared_ptr<Spell>> &GameStructures::getSpells() {
  return spells;
}

void GameStructures::addSpell(std::shared_ptr<Spell> spell) {
  spells.push_back(spell);
}

} // namespace structures
