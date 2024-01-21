#include "Spell.hpp"
void Spell::drawSpell() const { DrawCircleV(position, radius, BLACK); }

Vector2 Spell::getPosition() const { return position; }
Vector2 Spell::getSpeed() const { return speed; }

void Spell::setPosition(Vector2 newPosition) { position = newPosition; }
void Spell::setSpeed(Vector2 newSpeed) { speed = newSpeed; }

void Spell::update() { setPosition(Vector2Add(position, speed)); }
