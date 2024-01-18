#include "gameLoop.hpp"
#include <iostream>

namespace gameloop {

void upgrade(Player &player, int upgradeStation) {
  switch (upgradeStation) {
  case 1: // upgrade health
    std::cout << player.getPlayerStats().getHealth() << std::endl;
    player.upgradeHealth();
    std::cout << player.getPlayerStats().getHealth() << std::endl;
    break;

  case 2: // upgrade armor
    std::cout << player.getPlayerStats().getArmor() << std::endl;
    player.upgradeArmor();
    std::cout << player.getPlayerStats().getArmor() << std::endl;
    break;

  case 3: // upgrade speed
    std::cout << player.getPlayerStats().getSpeed() << std::endl;
    player.upgradeSpeed();
    std::cout << player.getPlayerStats().getSpeed() << std::endl;
    break;

  case 4:
    std::cout << "Mejorado el daño" << std::endl;
    break;
  }
}

void move(int key, int upgradeStation, InputSystem &inputSystem,
          PubSubSystem &pubSubSystem, Player &player) {

  auto result = inputSystem.pressKey(key);

  if (result.valid()) {
    auto action = result.value();
    if (action == ActionType::INTERACT) {
      // pubSubSystem.mute();
      upgrade(player, upgradeStation);
    }
    if (action == ActionType::QUIT) {
      // pubSubSystem.unmute();
    }
    pubSubSystem.publish(action);
  }
}

void gameLoop(Camera2D &camera, Player &player,
              structures::GameStructures &gameStructures,
              InputSystem &inputSystem, PubSubSystem &pubSubSystem) {

  std::vector<bool> upgradeStationsCollisions = {false, false, false, false};
  int upgradeStation = -1;

  while (!WindowShouldClose()) {
    Vector2 playerPosition = player.getActualPosition();

    for (int i = 0; i < upgradeStationsCollisions.size(); i++) {
      bool collision = CheckCollisionCircleRec(
          player.getActualPosition(), 50, gameStructures.getUpgradeStation(i));

      upgradeStationsCollisions[i] = collision;

      if (upgradeStationsCollisions[i]) {
        upgradeStation = i;
        break;
      }
    }

    // update
    // movement
    if (IsKeyDown(KEY_A)) {
      move(KEY_A, upgradeStation, inputSystem, pubSubSystem, player);
    }

    if (IsKeyDown(KEY_D)) {
      move(KEY_D, upgradeStation, inputSystem, pubSubSystem, player);
    }

    if (IsKeyDown(KEY_W)) {
      move(KEY_W, upgradeStation, inputSystem, pubSubSystem, player);
    }

    if (IsKeyDown(KEY_S)) {
      move(KEY_S, upgradeStation, inputSystem, pubSubSystem, player);
    }

    if (IsKeyDown(KEY_E)) {
      move(KEY_E, upgradeStation, inputSystem, pubSubSystem, player);
    }

    if (IsKeyDown(KEY_Q)) {
      move(KEY_Q, upgradeStation, inputSystem, pubSubSystem, player);
    }

    camera.target = (Vector2){playerPosition.x + 20, playerPosition.y + 20};
    // draw
    BeginDrawing();
    BeginMode2D(camera);

    ClearBackground(RAYWHITE);

    DrawText("WandSurvivors", 190, 200, 20, LIGHTGRAY);

    // draw character
    DrawCircleV(playerPosition, 50, MAROON);

    // draw safe zone
    DrawRectangleLines(300, 100, 1800, 1000, BLACK);

    // upgrading player stats
    DrawRectangle(600, 250, 40, 40, GREEN);     // health
    DrawRectangle(750, 250, 40, 40, LIGHTGRAY); // armor
    DrawRectangle(900, 250, 40, 40, YELLOW);    // speed
    DrawRectangle(1050, 250, 40, 40, RED);      // damage
    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
}
} // namespace gameloop
