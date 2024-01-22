#include "Spell.hpp"
void Spell::drawSpell() const { DrawCircleV(position, radius, BLACK); }

Vector2 Spell::getPosition() const { return position; }
float const Spell::getSpeed() const { return speed; }

void Spell::setPosition(Vector2 newPosition) { position = newPosition; }
const float Spell::getRadius() const { return radius; }

bool Spell::checkCollision(Vector2 pos1, Vector2 pos2, float radius1,
                           float radius2) {
  return CheckCollisionCircles(pos1, radius1, pos2, radius2);
}

void Spell::update(float deltaTime) {
  position = Vector2Add(position, Vector2Scale(direction, speed * deltaTime));
}

bool Spell::isOutOfBounds() const {
  return (position.x < 0 || position.x > GetScreenWidth() || position.y < 0 ||
          position.y > GetScreenHeight());
}
