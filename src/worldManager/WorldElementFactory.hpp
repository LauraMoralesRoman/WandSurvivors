#pragma once
#include "../entities/EnemyPrototype.hpp"
#include <memory>

class WorldElementFactory {
public:
  virtual std::shared_ptr<EnemyPrototype> createEnemyPrototype() const = 0;
  virtual ~WorldElementFactory() = default;
};
