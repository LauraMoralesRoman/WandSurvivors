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

// auxiliar functions

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

void move(int key, bool collision, InputSystem &inputSystem,
          PubSubSystem &pubSubSystem) {

  auto result = inputSystem.pressKey(key);

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
}

void gameSetup(Camera2D &camera, Vector2 &ballPosition) {

  // screen settings
  const int screenWidth = 1920;
  const int screenHeight = 1080;

  // camera settings
  camera.target = (Vector2){ballPosition.x + 20.0f, ballPosition.y + 20.0f};
  camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  InitWindow(screenWidth, screenHeight, "WandSurvivors");

  ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};

  SetTargetFPS(60);
}

void gameLoop(Camera2D &camera, Vector2 &ballPosition,
              Rectangle &upgradeStation, InputSystem &inputSystem,
              PubSubSystem &pubSubSystem) {

  while (!WindowShouldClose()) {
    bool isInUpgradeZone =
        CheckCollisionCircleRec(ballPosition, 50, upgradeStation);

    // update
    // movement
    if (IsKeyDown(KEY_A)) {
      move(KEY_A, isInUpgradeZone, inputSystem, pubSubSystem);
    }

    if (IsKeyDown(KEY_D)) {
      move(KEY_D, isInUpgradeZone, inputSystem, pubSubSystem);
    }

    if (IsKeyDown(KEY_W)) {
      move(KEY_W, isInUpgradeZone, inputSystem, pubSubSystem);
    }

    if (IsKeyDown(KEY_S)) {
      move(KEY_S, isInUpgradeZone, inputSystem, pubSubSystem);
    }

    if (IsKeyDown(KEY_E)) {
      move(KEY_E, isInUpgradeZone, inputSystem, pubSubSystem);
    }

    if (IsKeyDown(KEY_Q)) {
      move(KEY_Q, isInUpgradeZone, inputSystem, pubSubSystem);
    }

    camera.target = (Vector2){ballPosition.x + 20, ballPosition.y + 20};
    // draw
    BeginDrawing();
    BeginMode2D(camera);

    ClearBackground(RAYWHITE);

    DrawText("WandSurvivors", 190, 200, 20, LIGHTGRAY);

    // draw character
    DrawCircleV(ballPosition, 50, MAROON);

    // draw safe zone
    DrawRectangleLines(300, 100, 1800, 1000, BLACK);

    // upgrading player stats
    DrawRectangle(600, 250, 40, 40, GREEN);     // health
    DrawRectangle(650, 250, 40, 40, LIGHTGRAY); // armor
    DrawRectangle(700, 250, 40, 40, YELLOW);    // speed
    DrawRectangle(750, 250, 40, 40, RED);       // damage
    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
}

int main() {
  // Camera
  Camera2D camera = {0};

  Vector2 ballPosition;
  Rectangle upgradeStation = {600, 250, 20, 20};

  InputSystem &inputSystem = InputSystem::getInstance();
  inputSystemSetup(inputSystem);

  PubSubSystem &pubSubSystem = PubSubSystem::getInstance();
  pubSubSystemSetup(pubSubSystem, ballPosition);

  gameSetup(camera, ballPosition);
  gameLoop(camera, ballPosition, upgradeStation, inputSystem, pubSubSystem);

  return 0;
}
