#pragma once
#include "EnemyPrototype.hpp"
#include "Player.hpp"

class Enemy : public EnemyPrototype {
public:
  virtual void attack() const = 0;
  virtual void move(Player &player) = 0;
  virtual void draw() = 0;
  virtual ~Enemy() = default;
};
