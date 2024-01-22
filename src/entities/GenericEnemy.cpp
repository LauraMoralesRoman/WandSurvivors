#include "GenericEnemy.hpp"
#include "EnemyPrototype.hpp"
#include <iostream>

void GenericEnemy::move(Player &player) {
  Vector2 playerDirection = player.getActualPosition();
  Vector2 directionToPlayer =
      Vector2Normalize(Vector2Subtract(playerDirection, position));
  Vector2 speed = Vector2Scale(directionToPlayer, 3.0f);

  position = Vector2Add(position, speed);
}

void GenericEnemy::draw() { DrawCircleV(position, radius, ORANGE); }

float GenericEnemy::makeDamage() const { return stats.damage; }

void GenericEnemy::takeDamage(float damage) {
  float currentHealth = stats.health;
  float currentArmor = stats.armor;

  std::cout << "Current enemy" << this << "health:" << currentHealth
            << std::endl;
  stats.health = currentHealth - (damage - currentArmor);
  std::cout << "New enemy" << this << "health:" << stats.health << std::endl;
}

std::shared_ptr<EnemyPrototype> GenericEnemy::clone() const {
  return std::make_shared<GenericEnemy>(*this);
}

const EnemyStats GenericEnemy::getStats() const { return stats; }

const Vector2 GenericEnemy::getPosition() const { return position; }

void GenericEnemy::setPosition(Vector2 newPosition) { position = newPosition; }

const float GenericEnemy::getRadius() const { return radius; }

void GenericEnemy::setRadius(float newRadius) { radius = newRadius; }
