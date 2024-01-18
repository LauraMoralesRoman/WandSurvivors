#pragma once

#include "../include/raylib.h"
#include "entities/Player.hpp"
#include "gameStructures.hpp"
#include <spdlog/spdlog.h>
namespace gameSetup {

#define screenWidth 900
#define screenHeight 600

void pubSubSystemSetup(input_manager::pubSub::PubSubSystem &system,
                       Player &player, Vector2 &playerPosition);

void inputSystemSetup(input_manager::inputSystem::InputSystem &inputSystem);

void initUpgradeStations(structures::GameStructures &gameStructures);

void setup(Camera2D &camera, Player &player);
} // namespace gameSetup
