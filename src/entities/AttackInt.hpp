#pragma once

class AttackInt {
public:
  virtual float makeDamage() const = 0;
  virtual void takeDamage(float damage) = 0;
  virtual ~AttackInt() = default;
};
