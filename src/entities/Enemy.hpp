#pragma once
#include "AttackInt.hpp"
#include "EnemyPrototype.hpp"
#include "Player.hpp"

class Enemy : public virtual EnemyPrototype, public virtual AttackInt {
public:
  virtual void move(Player &player) = 0;
  virtual void draw() = 0;

  virtual float makeDamage() const override = 0;
  virtual void takeDamage(float damage) override = 0;
  virtual ~Enemy() = default;
};
