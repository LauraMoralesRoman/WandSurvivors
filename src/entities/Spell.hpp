#pragma once
#include "../../include/raylib.h"
#include "../../include/raymath.h"
class Spell {
public:
  Spell() = default;

  void drawSpell() const;

  Vector2 getPosition() const;
  Vector2 getSpeed() const;

  void setPosition(Vector2 newPosition);
  void setSpeed(Vector2 newSpeed);

  void update();

private:
  Vector2 position;
  Vector2 speed;
  float radius = 15.0f;
};
