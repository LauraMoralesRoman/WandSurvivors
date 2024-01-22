#include "gameLoop.hpp"
#include "entities/EnemyPrototype.hpp"
#include "entities/Player.hpp"
#include "entities/PlayerStat.hpp"
#include "entities/Wand.hpp"
#include "entities/WandStat.hpp"
#include "entities/upgradeStationsFacade/UpgradeStationFacade.hpp"
#include "gameContext.hpp"
#include "gameSetup.hpp"
#include "gameStructures.hpp"
#include "input_manager/InputSystem.hpp"
#include "input_manager/PubSubSystem.hpp"
#include "raylib.h"
#include "worldManager/GenericEnemyFactory.hpp"
#include "worldManager/WorldElementFactory.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>
#include <vector>

namespace gameloop {

void gameLoop(game::Context &ctx) {

  std::srand(std::time(0));

  Vector2 initialPlayerPosition = {.x = (float)gameSetup::screenWidth / 2,
                                   .y = (float)gameSetup::screenHeight / 2};

  // initialize objects
  //

  // player
  PlayerStat playerInitialStats(10.0f, 5.0f, 2.0f);
  WandStat basicWandStats(7.5f, WandType::FIRE);
  Wand fireWand(1, basicWandStats);
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
  auto &upgradeFacade = facade::UpgradeStationFacade::getInstance();

  // ENEMY SPAWN
  int maxEnemies = gameStructures.getMaxEnemies();
  GenericEnemyFactory genericEnemySpawner;
  std::shared_ptr<EnemyPrototype> genericPrototype =
      genericEnemySpawner.createEnemyPrototype();

  // Get mapped keys
  auto mappedKeys = inputSystem.getMappedKeys();

  double accumulatedTime = 0.0;
  const double maxAccumulatedTime = 1.0 / 30.0;
  // loop
  while (!WindowShouldClose() && ctx.alive) {
    double deltaTime = GetFrameTime();
    accumulatedTime += deltaTime;

    if (accumulatedTime > maxAccumulatedTime)
      accumulatedTime = maxAccumulatedTime;

    Vector2 playerPosition = player.getActualPosition();
    Vector2 mousePosition = GetMousePosition();

    Vector2 adjustedMousePosition =
        GetScreenToWorld2D(mousePosition, ctx.camera);
    //////////////////////////////
    // UPGRADE STATION COLLISION//
    //////////////////////////////
    for (const auto &upgradeStation : gameStructures.getUpgradeStations()) {
      upgradeStation->isInside(player.getActualPosition(), 50.0f);
    }

    /////////////////
    // ENEMY SPAWN //
    /////////////////
    if (gameStructures.getGenericEnemies().size() < maxEnemies) {
      float newX = std::rand() % 301;
      float newY = std::rand() % 451;
      Vector2 enemyPosition = {newX, newY};
      auto enemy = std::make_shared<GenericEnemy>(
          *std::dynamic_pointer_cast<GenericEnemy>(genericPrototype->clone()));
      enemy->setPosition(enemyPosition);
      gameStructures.addEnemy(*enemy);
    }

    /////////////////////
    // enemies movement//
    /////////////////////
    for (auto &enemy : gameStructures.getGenericEnemies()) {
      enemy->move(player);
    }

    //////////////////////
    // check user inputs//
    //////////////////////
    for (const auto &key : mappedKeys) {
      if (IsKeyDown(key) || IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        const auto &mappedActionRes = inputSystem.pressKey(key);
        if (mappedActionRes.valid()) {
          pubsubSystem.publish(mappedActionRes.value()); // move

          if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {

            auto newSpell = player.getPlayerWands().at(0).castSpell(
                playerPosition, adjustedMousePosition); // cast spell

            gameStructures.addSpell(newSpell);
          }

          for (const auto &upgradeStation :
               gameStructures.getUpgradeStations()) {
            if (upgradeStation->isPlayerInside() && IsKeyDown(KEY_E)) {
              std::cout << "Current health:" << player.getPlayerStats().health
                        << std::endl;
              std::cout << "Current armor:" << player.getPlayerStats().armor
                        << std::endl;
              std::cout << "Current speed:" << player.getPlayerStats().speed
                        << std::endl;
              std::cout << "Current damage:"
                        << player.getPlayerWands().at(0).getWandStats().damage
                        << std::endl;
              int stationColor = ColorToInt(upgradeStation->getColor());

              if (stationColor == ColorToInt(GREEN))
                upgradeFacade.upgradeHealth(player.getPlayerStats().health);

              if (stationColor == ColorToInt(YELLOW))
                upgradeFacade.upgradeArmor(player.getPlayerStats().armor);

              if (stationColor == ColorToInt(BLUE))
                upgradeFacade.upgradeSpeed(player.getPlayerStats().speed);

              if (stationColor == ColorToInt(RED)) {
                float damage =
                    player.getPlayerWands().at(0).getWandStats().damage;
                upgradeFacade.upgradeDamage(damage);
                WandStat newWandStats(damage, WandType::FIRE);
                player.getPlayerWands().at(0).setWandStats(newWandStats);
              }
            }
          }
        }
      }
    }

    //
    //
    // Update spell
    //
    //
    for (auto &spell : gameStructures.getSpells()) {
      spell->update(deltaTime);
    }

    gameStructures.getSpells().erase(
        std::remove_if(gameStructures.getSpells().begin(),
                       gameStructures.getSpells().end(),
                       [&](const std::shared_ptr<Spell> &s) {
                         return (s->getPosition().x < 0 ||
                                 s->getPosition().x > gameSetup::screenWidth ||
                                 s->getPosition().y < 0 ||
                                 s->getPosition().y > gameSetup::screenHeight);
                       }),
        gameStructures.getSpells().end());

    ////////////////////////
    // check enemy damage
    //
    //
    //
    for (const auto &enemy : gameStructures.getGenericEnemies()) {
      if (CheckCollisionCircles(player.getActualPosition(), 50,
                                enemy->getPosition(), enemy->getRadius())) {
        float damage = enemy->makeDamage();
        player.takeDamage(damage);
      }
    }

    if (player.getPlayerStats().health < 0.0f)
      ctx.alive = false;

    // check player damage
    //

    for (const auto &enemy : gameStructures.getGenericEnemies()) {
      for (const auto &spell : gameStructures.getSpells()) {
        if (spell->checkCollision(spell->getPosition(), enemy->getPosition(),
                                  spell->getRadius(), enemy->getRadius())) {

          float damage = player.makeDamage();
          enemy->takeDamage(damage);
        }
      }
    }

    int totalEnemies = gameStructures.getGenericEnemies().size();

    gameStructures.deleteEnemy();

    if (gameStructures.getGenericEnemies().size() != totalEnemies) {
      std::cout << "KDA:" << ctx.enemiesKilled << std::endl;
      ctx.enemiesKilled += 5 - gameStructures.getGenericEnemies().size();
      std::cout << "KDA:" << ctx.enemiesKilled << std::endl;
    }

    //
    //
    // CAMERA
    //
    //
    //

    ctx.camera.target = (Vector2){playerPosition.x + 20, playerPosition.y + 20};

    accumulatedTime -= deltaTime;
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

    // draw limits

    DrawLine(0, 0, gameSetup::screenWidth, 0, BLACK);  // Línea superior
    DrawLine(0, 0, 0, gameSetup::screenHeight, BLACK); // Línea izquierda
    DrawLine(gameSetup::screenWidth - 1, 0, gameSetup::screenWidth - 1,
             gameSetup::screenHeight,
             BLACK); // Línea derecha
    DrawLine(0, gameSetup::screenHeight - 1, gameSetup::screenWidth,
             gameSetup::screenHeight - 1,
             BLACK); // Línea inferior

    // draw character
    DrawCircleV(playerPosition, 50, MAROON);

    // draw safe zone
    DrawRectangleLines(300, 100, 1800, 1000, BLACK);

    // draw upgrading player stats zone

    for (const auto &station : gameStructures.getUpgradeStations()) {
      station->draw();
    }

    DrawRectangle(600, 250, 40, 40, GREEN);  // health
    DrawRectangle(750, 250, 40, 40, YELLOW); // armor
    DrawRectangle(900, 250, 40, 40, BLUE);   // speed
    DrawRectangle(1050, 250, 40, 40, RED);   // damage

    for (const auto &spell : gameStructures.getSpells()) {
      spell->drawSpell();
    }

    for (const auto &enemy : gameStructures.getGenericEnemies()) {
      enemy->draw();
    }

    EndMode2D();
    EndDrawing();
  }
  CloseWindow();
}
} // namespace gameloop
