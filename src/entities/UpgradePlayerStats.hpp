#pragma once

#include "UpgradeStation.hpp"

class UpgradePlayerStats : public UpgradeStation {
public:
  void upgradeHealth(Player &player) override;

  void upgradeSpeed(Player &player) override;

  void upgradeArmor(Player &player) override;
};
