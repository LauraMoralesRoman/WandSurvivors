#include "GenericEnemy.hpp"
#include "EnemyPrototype.hpp"
#include <iostream>

void GenericEnemy::attack() const {
  // TODO attack player
}

void GenericEnemy::move(Player &player) {
  // TODO: movimiento hacia el jugador
}

// it doesnt work with circles idk why
void GenericEnemy::draw() {
  // Vector2 v1 = position;
  // Vector2 v2 = {position.x + 200.0f, position.y};
  // Vector2 v3 = {position.x + 100.0f, position.y};
  std::cout << "Drawing the enemy" << std::endl;
  DrawCircleV(position, 50, ORANGE);
  // DrawTriangle(v1, v2, v3, BLACK);
}

EnemyPrototype *GenericEnemy::clone() const { return new GenericEnemy(*this); }

const EnemyStats GenericEnemy::getStats() const { return stats; }

const Vector2 GenericEnemy::getPosition() const { return position; }

void GenericEnemy::setPosition(Vector2 newPosition) { position = newPosition; }
