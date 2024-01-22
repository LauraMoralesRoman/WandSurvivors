#pragma once

class IntUpgradeStation {
public:
  virtual void upgradeHealth(float &health) = 0;
  virtual void upgradeArmor(float &armor) = 0;
  virtual void upgradeSpeed(float &speed) = 0;
  virtual void upgradeDamage(float &damage) = 0;
  virtual ~IntUpgradeStation() = default;
};
