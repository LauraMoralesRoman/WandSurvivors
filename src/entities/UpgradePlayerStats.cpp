#include "UpgradePlayerStats.hpp"
#include "Player.hpp"

void UpgradePlayerStats::upgradeHealth(Player &player) {
  auto stats = player.getPlayerStats();
  stats.setHealth(stats.getHealth() + 2.0f);
}

void UpgradePlayerStats::upgradeSpeed(Player &player) {
  auto stats = player.getPlayerStats();
  stats.setSpeed(stats.getSpeed() + 5.0f);
}

void UpgradePlayerStats::upgradeArmor(Player &player) {
  auto stats = player.getPlayerStats();
  stats.setArmor(stats.getArmor() + 1.0f);
}
