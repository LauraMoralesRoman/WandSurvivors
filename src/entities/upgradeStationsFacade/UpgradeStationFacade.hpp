#pragma once
#include "IntUpgradeStation.hpp"
#include "UpgradeArmorStation.hpp"
#include "UpgradeDamageStation.hpp"
#include "UpgradeHealthStation.hpp"
#include "UpgradeSpeedStation.hpp"

namespace facade {
class UpgradeStationFacade : public virtual IntUpgradeStation {
public:
  static UpgradeStationFacade &getInstance();
  void upgradeHealth(float &health) override;
  void upgradeArmor(float &armor) override;
  void upgradeSpeed(float &speed) override;
  void upgradeDamage(float &damage) override;

private:
  UpgradeStationFacade() {}
  ~UpgradeStationFacade() {}
  UpgradeStationFacade(const UpgradeStationFacade &) = delete;
  UpgradeStationFacade &operator=(const UpgradeStationFacade &) = delete;

  UpgradeHealthStation upgradeHealthStation;
  UpgradeArmorStation upgradeArmorStation;
  UpgradeSpeedStation upgradeSpeedStation;
  UpgradeDamageStation upgradeDamageStation;
};
} // namespace facade
