#include "gameLoop.hpp"
#include "entities/EnemyPrototype.hpp"
#include "entities/Player.hpp"
#include "entities/PlayerStat.hpp"
#include "entities/Wand.hpp"
#include "entities/WandStat.hpp"
#include "gameContext.hpp"
#include "gameSetup.hpp"
#include "input_manager/InputSystem.hpp"
#include "input_manager/PubSubSystem.hpp"
#include "raylib.h"
#include "worldManager/GenericEnemyFactory.hpp"
#include "worldManager/WorldElementFactory.hpp"
#include <iostream>
#include <vector>

#include <cstdlib>
#include <ctime>

namespace gameloop {

void gameLoop(game::Context &ctx) {

  std::srand(std::time(0));

  bool isSpellCasting = false;

  std::vector<GenericEnemy *> enemies;
  const int maxEnemies = 5;

  std::vector<bool> upgradeStationsCollisions = {false, false, false, false};
  int upgradeStation = -1;

  Vector2 initialPlayerPosition = {.x = (float)gameSetup::screenWidth / 2,
                                   .y = (float)gameSetup::screenHeight / 2};

  // initialize objects
  Spell spell;
  // player
  PlayerStat playerInitialStats(10.0f, 5.0f, 2.0f);
  WandStat basicWandStats(3.0f, WandType::FIRE);
  Wand fireWand(1, basicWandStats, spell);
  std::vector<Wand> initialWands = {fireWand};

  Player player;
  player.setActualPosition(initialPlayerPosition)
      .setWands(initialWands)
      .setStats(playerInitialStats);

  player.start(ctx);

  // Systems
  auto &gameStructures = structures::GameStructures::getInstance();
  auto &inputSystem = input_manager::inputSystem::InputSystem::getInstance();
  auto &pubsubSystem = input_manager::pubSub::PubSubSystem::getInstance();

  // ENEMY SPAWN
  GenericEnemyFactory genericEnemySpawner;
  EnemyPrototype *genericPrototype = genericEnemySpawner.createEnemyPrototype();

  // Get mapped keys
  auto mappedKeys = inputSystem.getMappedKeys();

  // loop
  while (!WindowShouldClose()) {
    Vector2 playerPosition = player.getActualPosition();

    // upgrade stations collisions
    for (int i = 0; i < upgradeStationsCollisions.size(); i++) {
      bool collision = CheckCollisionCircleRec(
          player.getActualPosition(), 50, gameStructures.getUpgradeStation(i));

      upgradeStationsCollisions[i] = collision;

      if (upgradeStationsCollisions[i]) {
        upgradeStation = i;
        break;
      }
    }

    //
    // enemy spawn
    //
    if (enemies.size() < maxEnemies) {
      float newX = std::rand() % 301;
      float newY = std::rand() % 451;
      Vector2 enemyPosition = {newX, newY};
      GenericEnemy *enemy =
          dynamic_cast<GenericEnemy *>(genericPrototype->clone());
      enemy->setPosition(enemyPosition);
      std::cout << "Generated enemy: " << enemy
                << "With coordenates:" << enemy->getPosition().x
                << enemy->getPosition().y << std::endl;
      enemies.push_back(enemy);
    }

    //
    //
    // DONT CHECK THIS!!!, i have to change it
    //
    //
    switch (upgradeStation) {
    case 1:
      std::cout << player.getPlayerStats().health << std::endl;
      player.upgradeHealth();
      std::cout << player.getPlayerStats().health << std::endl;
      break;
    case 2:
      std::cout << player.getPlayerStats().armor << std::endl;
      player.upgradeArmor();
      std::cout << player.getPlayerStats().armor << std::endl;
      break;
    case3:
      std::cout << player.getPlayerStats().speed << std::endl;
      player.upgradeSpeed();
      std::cout << player.getPlayerStats().speed << std::endl;
      break;
    }

    //
    //
    // check user inputs
    //
    //
    for (const auto &key : mappedKeys) {
      if (IsKeyDown(key) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        const auto &mappedActionRes = inputSystem.pressKey(key);
        if (mappedActionRes.valid()) {
          // Send notification to pubsub system
          pubsubSystem.publish(mappedActionRes.value());
        }
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
          isSpellCasting = true;
          player.getPlayerWands().at(0).getSpell().setPosition(
              player.getActualPosition());
        } else {
          isSpellCasting = false;
        }
      }
    }
    //
    //
    // Update spell
    //
    //
    //
    if (isSpellCasting) {
      player.getPlayerWands().at(0).getSpell().update();
      std::cout << "posicion x:"
                << player.getPlayerWands().at(0).getSpell().getPosition().x
                << std::endl;
      std::cout << "posicion y:"
                << player.getPlayerWands().at(0).getSpell().getPosition().y
                << std::endl;
    }
    //
    //
    //
    // CAMERA
    //
    //
    //

    ctx.camera.target = (Vector2){playerPosition.x + 20, playerPosition.y + 20};
    //
    //
    //
    // DRAW
    //
    //
    //
    BeginDrawing();
    BeginMode2D(ctx.camera);

    ClearBackground(RAYWHITE);

    DrawText("WandSurvivors", 190, 200, 20, LIGHTGRAY);

    // draw character
    DrawCircleV(playerPosition, 50, MAROON);

    // draw safe zone
    DrawRectangleLines(300, 100, 1800, 1000, BLACK);

    // upgrading player stats
    DrawRectangle(600, 250, 40, 40, GREEN);  // health
    DrawRectangle(750, 250, 40, 40, BLUE);   // armor
    DrawRectangle(900, 250, 40, 40, YELLOW); // speed
    DrawRectangle(1050, 250, 40, 40, RED);   // damage

    player.getPlayerWands().at(0).getSpell().drawSpell();

    for (const auto &enemy : enemies) {
      std::cout << "Enemy coordinates: (" << enemy->getPosition().x << ", "
                << enemy->getPosition().y << ")" << std::endl;
      enemy->draw();
    }

    EndMode2D();
    EndDrawing();
  }
  CloseWindow();

  for (GenericEnemy *enemy : enemies) {
    delete enemy;
  }
}
} // namespace gameloop
