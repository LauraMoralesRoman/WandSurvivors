#include "Player.hpp"
#pragma once

class UpgradeStation {
public:
  virtual void upgradeHealth(Player &player) {}

  virtual void upgradeSpeed(Player &player) {}

  virtual void upgradeArmor(Player &player) {}

  virtual void upgradeDamage(Player &player) {}

  virtual ~UpgradeStation() {}
};
