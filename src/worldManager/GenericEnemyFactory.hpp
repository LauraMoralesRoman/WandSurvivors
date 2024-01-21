#pragma once
#include "../entities/EnemyPrototype.hpp"
#include "../entities/GenericEnemy.hpp"
#include "WorldElementFactory.hpp"
class GenericEnemyFactory : public WorldElementFactory {
public:
  std::shared_ptr<EnemyPrototype> createEnemyPrototype() const override;
};
