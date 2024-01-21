#pragma once
#include "../entities/EnemyPrototype.hpp"
#include "../entities/GenericEnemy.hpp"
#include "WorldElementFactory.hpp"
class GenericEnemyFactory : public WorldElementFactory {
public:
  EnemyPrototype *createEnemyPrototype() const override;
};
