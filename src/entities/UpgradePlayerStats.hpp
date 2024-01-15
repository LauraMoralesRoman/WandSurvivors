#pragma once
#include "Player.hpp"

class UpgradePlayerStats {
public:
  virtual void upgradeHealth(Player &player) const = 0;

  virtual void upgradeSpeed(Player &player) const = 0;

  virtual void upgradeArmor(Player &player) const = 0;
};
