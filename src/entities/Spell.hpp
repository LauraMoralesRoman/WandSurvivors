#pragma once
#include "../../include/raylib.h"
#include "../../include/raymath.h"
class Spell {
public:
  Spell(Vector2 initialPosition, Vector2 initialDirection)
      : position(initialPosition), direction(initialDirection) {}

  void drawSpell() const;

  Vector2 getPosition() const;
  const float getSpeed() const;
  const float getRadius() const;

  bool isOutOfBounds() const;
  void setPosition(Vector2 newPosition);
  bool checkCollision(Vector2 pos1, Vector2 pos2, float radius1, float radius2);
  void update(float deltaTime);

private:
  Vector2 position;
  Vector2 direction;
  float speed = 150.0f;
  float radius = 15.0f;
};
