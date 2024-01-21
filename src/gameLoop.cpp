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
#include <memory>
#include <vector>

#include <cstdlib>
#include <ctime>

namespace gameloop {

void gameLoop(game::Context &ctx) {

  std::srand(std::time(0));

  bool isSpellCasting = false;

  std::vector<std::shared_ptr<GenericEnemy>> enemies;
  const int maxEnemies = 5;

  std::vector<bool> upgradeStationsCollisions = {false, false, false, false};
  int upgradeStation = -1;

  Vector2 initialPlayerPosition = {.x = (float)gameSetup::screenWidth / 2,
                                   .y = (float)gameSetup::screenHeight / 2};

  // initialize objects
  Spell spell;
  // player
  PlayerStat playerInitialStats(10.0f, 5.0f, 2.0f);
  WandStat basicWandStats(7.5f, WandType::FIRE);
  Wand fireWand(1, basicWandStats, spell);
  std::vector<Wand> initialWands = {fireWand};

  Player player;
  player.setActualPosition(initialPlayerPosition)
      .setWands(initialWands)
      .setStats(playerInitialStats);

  player.start(ctx);
  bool alive = true;
  // Systems
  auto &gameStructures = structures::GameStructures::getInstance();
  auto &inputSystem = input_manager::inputSystem::InputSystem::getInstance();
  auto &pubsubSystem = input_manager::pubSub::PubSubSystem::getInstance();

  // ENEMY SPAWN
  GenericEnemyFactory genericEnemySpawner;
  std::shared_ptr<EnemyPrototype> genericPrototype =
      genericEnemySpawner.createEnemyPrototype();

  // Get mapped keys
  auto mappedKeys = inputSystem.getMappedKeys();

  // loop
  while (!WindowShouldClose() && alive) {
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
      auto enemy = std::make_shared<GenericEnemy>(
          *std::dynamic_pointer_cast<GenericEnemy>(genericPrototype->clone()));
      enemy->setPosition(enemyPosition);
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

    for (auto &enemy : enemies) {
      enemy->move(player);
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

    if (isSpellCasting)
      player.getPlayerWands().at(0).getSpell().update();

    // check enemy damage
    for (const auto &enemy : enemies) {
      if (CheckCollisionCircles(player.getActualPosition(), 50,
                                enemy->getPosition(), 20)) {
        float damage = enemy->makeDamage();
        player.takeDamage(damage);
      }
    }

    if (player.getPlayerStats().health < 0.0f) {
      alive = false;
    }
    // check player damage
    //

    for (const auto &enemy : enemies) {
      if (CheckCollisionCircles(
              enemy->getPosition(), 20,
              player.getPlayerWands().at(0).getSpell().getPosition(), 15)) {
        float damage = player.makeDamage();
        enemy->takeDamage(damage);
      }
    }

    enemies.erase(
        std::remove_if(enemies.begin(), enemies.end(),
                       [](const std::shared_ptr<GenericEnemy> &enemy) {
                         return enemy->getStats().health <= 0;
                       }),
        enemies.end());
    //
    //
    // CAMERA
    //
    //
    //

    ctx.camera.target = (Vector2){playerPosition.x + 20, playerPosition.y + 20};

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
      enemy->draw();
    }

    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
}
} // namespace gameloop
