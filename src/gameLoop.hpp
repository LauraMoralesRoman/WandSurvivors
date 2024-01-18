#pragma once
#include "entities/Player.hpp"
#include "gameStructures.hpp"
#include "input_manager/InputSystem.hpp"
#include "input_manager/PubSubSystem.hpp"
#include <vector>

namespace gameloop {

void upgrade(Player &player, int upgradeStation);
void move(int key, int upgradeStation, InputSystem &inputSystem,
          PubSubSystem &pubSubSystem, Player &player);
void gameLoop(Camera2D &camera, Player &player,
              structures::GameStructures &gameStructures,
              InputSystem &inputSystem, PubSubSystem &pubSubSystem);

} // namespace gameloop
