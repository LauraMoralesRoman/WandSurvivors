#include "gameSetup.hpp"
#include "gameContext.hpp"
#include "gameStructures.hpp"
#include "input_manager/InputSystem.hpp"

namespace gameSetup {
void initUpgradeStations(game::Context& ctx) {
	Rectangle upgradeHealthStation = {600, 250, 50, 50};
	Rectangle upgradeArmorStation = {750, 250, 50, 50};
	Rectangle upgradeSpeedStation = {900, 250, 50, 50};
	Rectangle upgradeDamageStation = {1050, 250, 50, 50};

	auto& gameStructures = structures::GameStructures::getInstance();

	gameStructures.addUpgradeStation(upgradeHealthStation);
	gameStructures.addUpgradeStation(upgradeArmorStation);
	gameStructures.addUpgradeStation(upgradeSpeedStation);
	gameStructures.addUpgradeStation(upgradeDamageStation);
}

void setup(game::Context& ctx) {
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
	auto& inputSystem = input_manager::inputSystem::InputSystem::getInstance();
	using ActionType = input_manager::inputSystem::ActionType;

	inputSystem.mapKeyToAction(KEY_A, ActionType::MOVE_LEFT);
	inputSystem.mapKeyToAction(KEY_D, ActionType::MOVE_RIGHT);
	inputSystem.mapKeyToAction(KEY_W, ActionType::MOVE_UP);
	inputSystem.mapKeyToAction(KEY_S, ActionType::MOVE_DOWN);
	inputSystem.mapKeyToAction(MOUSE_BUTTON_LEFT, ActionType::ATTACK);
	inputSystem.mapKeyToAction(KEY_E, ActionType::INTERACT);
	inputSystem.mapKeyToAction(KEY_Q, ActionType::QUIT);
}
