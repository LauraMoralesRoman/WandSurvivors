#include "../include/raylib.h"
#include "CombinedScore.hpp"
#include "EnemiesKilledScore.hpp"
#include "PointSystem.hpp"
#include "TimeSurvivedScore.hpp"
#include "gameContext.hpp"
#include "gameLoop.hpp"
#include "gameSetup.hpp"
#include <chrono>
#include <iostream>
#include <spdlog/spdlog.h>

int main() {
  // Camera
  Camera2D camera = {.offset = {.x = 0.0, .y = 0.0}};

  game::Context ctx{
      .alive = true,
      .isSpellCasting = false,
      .enemiesKilled = 0,
      .camera = camera,
  };

  auto timeSurvivedStrategy = std::make_shared<TimeSurvivedScore>();
  auto enemiesKilledStrategy = std::make_shared<EnemiesKilledScore>();
  auto combinedStrategy = std::make_shared<CombinedScore>();
  PointSystem pointsSystem(timeSurvivedStrategy);

  auto start_time = std::chrono::high_resolution_clock::now();

  gameSetup::initUpgradeStations(ctx);
  gameSetup::inputSystemSetup();
  gameSetup::setup(ctx);
  gameloop::gameLoop(ctx);

  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
      end_time - start_time);

  int score1 = pointsSystem.calculateScore(duration.count(), 0);
  std::cout << "Puntuacion tiempo de supervivencia: " << score1 << std::endl;

  pointsSystem.setScoreStrategy(enemiesKilledStrategy);

  int score2 = pointsSystem.calculateScore(duration.count(), ctx.enemiesKilled);
  std::cout << "Total enemigos eliminados: " << ctx.enemiesKilled << std::endl;
  std::cout << "Puntuación enemigos eliminados: " << score2 << std::endl;
  return 0;
}
