#include "../include/raylib.h"
#include "input_manager/InputSystem.hpp"
#include "input_manager/PubSubSystem.hpp"
#include <functional>
#include <iostream>
#include <spdlog/spdlog.h>

using namespace input_manager::inputSystem;
using namespace input_manager::pubSub;

void setupMovementFunctions(Vector2 &ballPosition) {
  std::function<void()> moveUp = [&ballPosition]() { ballPosition.y -= 2.0f; };

  std::function<void()> moveDown = [&ballPosition]() {
    ballPosition.y += 2.0f;
  };

  std::function<void()> moveRight = [&ballPosition]() {
    ballPosition.x += 2.0f;
  };

  std::function<void()> moveLeft = [&ballPosition]() {
    ballPosition.x -= 2.0f;
  };
}

// TODO:cambiar el parametro de subscribe
void pubSubSystemSetup(PubSubSystem &pubSubSystem) {
  // pubSubSystem.subscribe(ActionType::MOVE_UP, setupMovementFunctions);
}

void inputSystemSetup(InputSystem &inputSystem) {
  inputSystem.mapKeyToAction(SDLK_a, ActionType::MOVE_LEFT);
  inputSystem.mapKeyToAction(SDLK_d, ActionType::MOVE_RIGHT);
  inputSystem.mapKeyToAction(SDLK_w, ActionType::MOVE_UP);
  inputSystem.mapKeyToAction(SDLK_s, ActionType::MOVE_DOWN);
}

void gameSetup(Vector2 &ballPosition) {
  InputSystem inputSystem;
  inputSystemSetup(inputSystem);

  // screen settings
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "WandSurvivors");

  ballPosition = {(float)screenWidth / 2, (float)screenHeight / 2};

  SetTargetFPS(60);
}

void gameLoop(Vector2 &ballPosition) {
  while (!WindowShouldClose()) {
    // update

    // draw
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawText("WandSurvivors", 190, 200, 20, LIGHTGRAY);

    // draw character
    DrawCircleV(ballPosition, 50, MAROON);

    EndDrawing();
  }
  CloseWindow();
}

int main() {

  Vector2 ballPosition;
  gameSetup(ballPosition);
  gameLoop(ballPosition);

  return 0;
}
