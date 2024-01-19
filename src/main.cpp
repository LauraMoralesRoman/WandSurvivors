#include "../include/raylib.h"
#include "gameContext.hpp"
#include "gameLoop.hpp"
#include "gameSetup.hpp"
#include <spdlog/spdlog.h>

int main() {
	// Camera
	Camera2D camera = {
		.offset = { .x = 0.0, .y = 0.0 }
	};

	game::Context ctx {
		.camera = camera,
	};
	gameSetup::initUpgradeStations(ctx);

	gameSetup::inputSystemSetup();
	gameSetup::setup(ctx);
	gameloop::gameLoop(ctx);

	return 0;
}
