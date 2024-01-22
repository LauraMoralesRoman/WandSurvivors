#pragma once

#include "raylib.h"

namespace game {
struct Context {
  bool alive;
  bool isSpellCasting;
  int enemiesKilled;
  Camera2D camera;
};
} // namespace game
