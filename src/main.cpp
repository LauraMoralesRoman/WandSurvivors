#include "../include/raylib.h"
#include "entities/Player.hpp"
#include "input_manager/InputSystem.hpp"
#include "input_manager/PubSubSystem.hpp"
#include <functional>
#include <iostream>
#include <spdlog/spdlog.h>
#include <vector>

using namespace input_manager::inputSystem;
using namespace input_manager::pubSub;

void pubSubSystemSetup(PubSubSystem &system, Vector2 &ballPosition) {

  std::function<void()> moveUp = [&ballPosition]() { ballPosition.y -= 20.0f; };

  std::function<void()> moveDown = [&ballPosition]() {
    ballPosition.y += 20.0f;
  };

  std::function<void()> moveRight = [&ballPosition]() {
    ballPosition.x += 20.0f;
  };

  std::function<void()> moveLeft = [&ballPosition]() {
    ballPosition.x -= 20.0f;
  };

  system.subscribe(ActionType::MOVE_UP, moveUp);
  system.subscribe(ActionType::MOVE_DOWN, moveDown);
  system.subscribe(ActionType::MOVE_RIGHT, moveRight);
  system.subscribe(ActionType::MOVE_LEFT, moveLeft);
}

void inputSystemSetup(InputSystem &inputSystem) {
  inputSystem.mapKeyToAction(KEY_A, ActionType::MOVE_LEFT);
  inputSystem.mapKeyToAction(KEY_D, ActionType::MOVE_RIGHT);
  inputSystem.mapKeyToAction(KEY_W, ActionType::MOVE_UP);
  inputSystem.mapKeyToAction(KEY_S, ActionType::MOVE_DOWN);
  inputSystem.mapKeyToAction(KEY_E, ActionType::INTERACT);
  inputSystem.mapKeyToAction(KEY_Q, ActionType::QUIT);
}

void gameSetup(Vector2 &ballPosition) {

  // screen settings
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "WandSurvivors");

  ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};

  SetTargetFPS(60);
}

void gameLoop(Vector2 &ballPosition, Rectangle &upgradeStation,
              InputSystem &inputSystem, PubSubSystem &pubSubSystem) {
  while (!WindowShouldClose()) {
    bool collision = CheckCollisionCircleRec(ballPosition, 50, upgradeStation);

    // update
    int keyPressed = GetKeyPressed();
    auto result = inputSystem.pressKey(keyPressed);

    if (result.valid()) {
      auto action = result.value();
      if (action == ActionType::INTERACT && collision) {
        pubSubSystem.mute();
      }
      if (action == ActionType::QUIT) {
        pubSubSystem.unmute();
      }
      pubSubSystem.publish(action);
    }

    // draw
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("WandSurvivors", 190, 200, 20, LIGHTGRAY);

    // draw character
    DrawCircleV(ballPosition, 50, MAROON);

    DrawRectangle(600, 250, 20, 20, GREEN);
    EndDrawing();
  }
  CloseWindow();
}

int main() {
  Vector2 ballPosition;
  Rectangle upgradeStation = {600, 250, 20, 20};

  InputSystem &inputSystem = InputSystem::getInstance();
  inputSystemSetup(inputSystem);

  PubSubSystem &pubSubSystem = PubSubSystem::getInstance();
  pubSubSystemSetup(pubSubSystem, ballPosition);

  gameSetup(ballPosition);
  gameLoop(ballPosition, upgradeStation, inputSystem, pubSubSystem);

  return 0;
}
