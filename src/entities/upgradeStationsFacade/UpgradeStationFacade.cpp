#include "UpgradeStationFacade.hpp"

facade::UpgradeStationFacade &facade::UpgradeStationFacade::getInstance() {
  static UpgradeStationFacade instance;
  return instance;
}

void facade::UpgradeStationFacade::upgradeHealth(float &health) {
  upgradeHealthStation.upgradeHealth(health);
}

void facade::UpgradeStationFacade::upgradeArmor(float &armor) {
  upgradeArmorStation.upgradeArmor(armor);
}

void facade::UpgradeStationFacade::upgradeSpeed(float &speed) {
  upgradeSpeedStation.upgradeSpeed(speed);
}

void facade::UpgradeStationFacade::upgradeDamage(float &damage) {
  upgradeDamageStation.upgradeDamage(damage);
}
