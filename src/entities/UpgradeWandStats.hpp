#pragma once
#include "Player.hpp"

class UpgradeWandStats {
public:
  virtual void upgradeDamage(Player &player) const = 0;
};
