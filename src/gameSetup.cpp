#include "gameSetup.hpp"

using namespace input_manager::inputSystem;
using namespace input_manager::pubSub;

namespace gameSetup {
void pubSubSystemSetup(PubSubSystem &system, Player &player,
                       Vector2 &playerPosition) {
  std::function<void()> moveUp = [&player, &playerPosition]() {
    playerPosition.y -= 20.0f;
    player.setActualPosition(playerPosition);
  };

  std::function<void()> moveDown = [&player, &playerPosition]() {
    playerPosition.y += 20.0f;
    player.setActualPosition(playerPosition);
  };

  std::function<void()> moveRight = [&player, &playerPosition]() {
    playerPosition.x += 20.0f;
    player.setActualPosition(playerPosition);
  };

  std::function<void()> moveLeft = [&player, &playerPosition]() {
    playerPosition.x -= 20.0f;
    player.setActualPosition(playerPosition);
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

void initUpgradeStations(structures::GameStructures &gameStructures) {
  Rectangle upgradeHealthStation = {600, 250, 50, 50};
  Rectangle upgradeArmorStation = {750, 250, 50, 50};
  Rectangle upgradeSpeedStation = {900, 250, 50, 50};
  Rectangle upgradeDamageStation = {1050, 250, 50, 50};

  gameStructures.addUpgradeStation(upgradeHealthStation);
  gameStructures.addUpgradeStation(upgradeArmorStation);
  gameStructures.addUpgradeStation(upgradeSpeedStation);
  gameStructures.addUpgradeStation(upgradeDamageStation);
}

void setup(Camera2D &camera, Player &player) {

  Vector2 initialPosition = player.getActualPosition();
  // camera settings
  camera.target =
      (Vector2){initialPosition.x + 20.0f, initialPosition.y + 20.0f};
  camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;

  InitWindow(screenWidth, screenHeight, "WandSurvivors");

  SetTargetFPS(60);
}
} // namespace gameSetup
