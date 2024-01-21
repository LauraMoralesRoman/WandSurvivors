#pragma once

#include "gameContext.hpp"
#include "gameStructures.hpp"
#include <spdlog/spdlog.h>

namespace gameSetup {
constexpr unsigned int screenWidth = 900;
constexpr unsigned int screenHeight = 600;

void initUpgradeStations(game::Context &ctx);

void setup(game::Context &ctx);
void inputSystemSetup();
} // namespace gameSetup
