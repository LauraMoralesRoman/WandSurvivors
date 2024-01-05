#pragma once

#include "UpgradeStation.hpp"

class UpgradeWandStats : public UpgradeStation {
public:
  void upgradeDamage(Player &player) override;
};
