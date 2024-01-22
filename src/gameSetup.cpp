#include "gameSetup.hpp"
#include "entities/UpgradeShop.hpp"
#include "gameContext.hpp"
#include "gameStructures.hpp"
#include "input_manager/InputSystem.hpp"

namespace gameSetup {
void initUpgradeStations(game::Context &ctx) {
  UpgradeShop upgradeHealthShop = {Vector2{600, 250}, 50, 50, GREEN};
  UpgradeShop upgradeArmorShop = {Vector2{750, 250}, 50, 50, YELLOW};
  UpgradeShop upgradeSpeedShop = {Vector2{900, 250}, 50, 50, BLUE};
  UpgradeShop upgradeDamageShop = {Vector2{1050, 250}, 50, 50, RED};

  auto &gameStructures = structures::GameStructures::getInstance();

  gameStructures.addUpgradeStation(
      std::make_shared<UpgradeShop>(upgradeHealthShop));
  gameStructures.addUpgradeStation(
      std::make_shared<UpgradeShop>(upgradeArmorShop));
  gameStructures.addUpgradeStation(
      std::make_shared<UpgradeShop>(upgradeSpeedShop));
  gameStructures.addUpgradeStation(
      std::make_shared<UpgradeShop>(upgradeDamageShop));
}

void setup(game::Context &ctx) {
  // TODO: when this works pls
  // Vector2 initialPosition = ctx.player.getActualPosition();
  // // ctx.cam settings
  // ctx.cam.target =
  // 	(Vector2){initialPosition.x + 20.0f, initialPosition.y + 20.0f};
  ctx.camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  ctx.camera.rotation = 0.0f;
  ctx.camera.zoom = 1.0f;

  InitWindow(screenWidth, screenHeight, "WandSurvivors");

  SetTargetFPS(60);
}
} // namespace gameSetup

void gameSetup::inputSystemSetup() {
  auto &inputSystem = input_manager::inputSystem::InputSystem::getInstance();
  using ActionType = input_manager::inputSystem::ActionType;

  inputSystem.mapKeyToAction(KEY_A, ActionType::MOVE_LEFT);
  inputSystem.mapKeyToAction(KEY_D, ActionType::MOVE_RIGHT);
  inputSystem.mapKeyToAction(KEY_W, ActionType::MOVE_UP);
  inputSystem.mapKeyToAction(KEY_S, ActionType::MOVE_DOWN);
  inputSystem.mapKeyToAction(MOUSE_BUTTON_LEFT, ActionType::ATTACK);
  inputSystem.mapKeyToAction(KEY_L, ActionType::ATTACK);
  inputSystem.mapKeyToAction(KEY_E, ActionType::INTERACT);
  inputSystem.mapKeyToAction(KEY_Q, ActionType::QUIT);
}
