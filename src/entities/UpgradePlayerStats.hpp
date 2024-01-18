#pragma once

class UpgradePlayerStats {
public:
  virtual void upgradeHealth() = 0;

  virtual void upgradeSpeed() = 0;

  virtual void upgradeArmor() = 0;
};
