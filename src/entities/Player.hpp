#include "../../include/raylib.h"
#include "PlayerInputHandler.hpp"
#include "PlayerStat.hpp"
#include "UpgradePlayerStats.hpp"
#include "Wand.hpp"
#include <list>
#pragma once

class Player : public PlayerInputHandler, public UpgradePlayerStats {
public:
  Player(Vector2 initialPosition, PlayerStat initialStats,
         std::list<Wand> initialWands)
      : actualPosition(initialPosition), stats(initialStats),
        wands(initialWands) {}

  Vector2 getActualPosition() const;
  void setActualPosition(Vector2 newPosition);

  PlayerStat getPlayerStats() const;

  // upgrade stats
  void upgradeHealth() override {
    stats.setHealth(getPlayerStats().getHealth() + 5.0f);
  }

  void upgradeArmor() override {
    stats.setArmor(getPlayerStats().getArmor() + 5.0f);
  }

  void upgradeSpeed() override {
    stats.setSpeed(getPlayerStats().getSpeed() + 0.5f);
  }

  std::list<Wand> getPlayerWands() const;
  void addNewWand(Wand &wand);
  void deleteWand(Wand &wand);

  // pubsub
  void subscribe(ActionType action, PubSubSystem::Callback callBack) override {
    PubSubSystem &pubSubSystem = PubSubSystem::getInstance();
    pubSubSystem.subscribe(action, callBack);
  }

  void mute() override {
    PubSubSystem &pubSubSystem = PubSubSystem::getInstance();
    pubSubSystem.mute();
  }

  void unmute() override {
    PubSubSystem &pubSubSystem = PubSubSystem::getInstance();
    pubSubSystem.unmute();
  }

private:
  Vector2 actualPosition;
  PlayerStat stats;
  std::list<Wand> wands;
};
