#pragma once
#include "../entities/EnemyPrototype.hpp"

class WorldElementFactory {
public:
  virtual EnemyPrototype *createEnemyPrototype() const = 0;
  virtual ~WorldElementFactory() = default;
};
