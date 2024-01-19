#include "gameLoop.hpp"
#include "entities/Player.hpp"
#include "entities/PlayerStat.hpp"
#include "entities/Wand.hpp"
#include "entities/WandStat.hpp"
#include "gameContext.hpp"
#include "gameSetup.hpp"
#include "input_manager/InputSystem.hpp"
#include "input_manager/PubSubSystem.hpp"
#include "raylib.h"
#include <vector>

namespace gameloop {

void gameLoop(game::Context& ctx) {

  std::vector<bool> upgradeStationsCollisions = {false, false, false, false};
  int upgradeStation = -1;

  Vector2 initialPlayerPosition = {
			.x = (float)gameSetup::screenWidth / 2,
			.y = (float)gameSetup::screenHeight / 2
	};

  // initialize objects
  // player
  PlayerStat playerInitialStats(10.0f, 5.0f, 2.0f);
  WandStat basicWandStats(3.0f, WandType::FIRE);
  Wand fireWand(1, basicWandStats);
  std::vector<Wand> initialWands = {fireWand};

	Player player;
	player
		.setActualPosition(initialPlayerPosition)
		.setWands(initialWands)
		.setStats(playerInitialStats);

	player.start(ctx);

	// Systems
	auto& gameStructures = structures::GameStructures::getInstance();
	auto& inputSystem = input_manager::inputSystem::InputSystem::getInstance();
	auto& pubsubSystem = input_manager::pubSub::PubSubSystem::getInstance();

	// Get mapped keys
	auto mappedKeys = inputSystem.getMappedKeys();

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

		for (const auto& key : mappedKeys) {
			if (IsKeyDown(key)) {
				const auto& mappedActionRes = inputSystem.pressKey(key);
				if (mappedActionRes.valid()) {
					// Send notification to pubsub system
					pubsubSystem.publish(mappedActionRes.value());
				}
			}
		}

    ctx.camera.target = (Vector2){playerPosition.x + 20, playerPosition.y + 20};
    // draw
    BeginDrawing();
    BeginMode2D(ctx.camera);

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
