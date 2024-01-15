#include "../../include/raylib.h"
#include "PlayerInputHandler.hpp"
#include "PlayerStat.hpp"
#include "Wand.hpp"
#include <list>
#pragma once

class Player : public PlayerInputHandler {
public:
  Player(Vector2 initialPosition, PlayerStat initialStats,
         std::list<Wand> initialWands)
      : actualPosition(initialPosition), stats(initialStats),
        wands(initialWands) {}

  Vector2 getActualPosition() const;
  void setActualPosition(Vector2 newPosition);

  Vector2 getTargetPosition() const;
  void setTargetPosition(Vector2 newTargetPosition);

  PlayerStat getPlayerStats() const;
  void setPlayerStats(float newHealth, float newArmor, float newSpeed);

  std::list<Wand> getPlayerWands() const;
  void addNewWand(Wand wand);
  void deleteWand(Wand wand);

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
  Vector2 targetPosition;
  PlayerStat stats;
  std::list<Wand> wands;
};
