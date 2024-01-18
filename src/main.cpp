#include "../include/raylib.h"
#include "entities/WandStat.hpp"
#include "gameLoop.hpp"
#include "gameSetup.hpp"
#include "gameStructures.hpp"
#include "input_manager/InputSystem.hpp"
#include "input_manager/PubSubSystem.hpp"
#include <spdlog/spdlog.h>

int main() {
  // Camera
  Camera2D camera = {0};

  Vector2 initialPlayerPosition = {(float)screenWidth / 2,
                                   (float)screenHeight / 2};

  // initialize objects
  // player
  PlayerStat playerInitialStats(10.0f, 5.0f, 2.0f);
  WandStat basicWandStats(3.0f, WandType::FIRE);
  Wand fireWand(1, basicWandStats);
  std::list<Wand> initialWands = {fireWand};
  Player player(initialPlayerPosition, playerInitialStats, initialWands);

  // game structures
  structures::GameStructures &gameStructures =
      structures::GameStructures::getInstance();

  gameSetup::initUpgradeStations(gameStructures);

  // systems
  InputSystem &inputSystem = InputSystem::getInstance();
  gameSetup::inputSystemSetup(inputSystem);

  PubSubSystem &pubSubSystem = PubSubSystem::getInstance();
  gameSetup::pubSubSystemSetup(pubSubSystem, player, initialPlayerPosition);

  gameSetup::setup(camera, player);
  gameloop::gameLoop(camera, player, gameStructures, inputSystem, pubSubSystem);

  return 0;
}
