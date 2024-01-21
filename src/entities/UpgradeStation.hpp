#pragma once
#include "Player.hpp"

class UpgradeStation {
public:
  virtual void upgradeHealth(Player &player) = 0;
  virtual void upgradeArmor(Player &player) = 0;
  virtual void upgradeSpeed(Player &player) = 0;
  virtual void upgradeDamaage(Player &player) = 0;
};
