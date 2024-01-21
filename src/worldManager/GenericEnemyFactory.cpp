#include "GenericEnemyFactory.hpp"

EnemyPrototype *GenericEnemyFactory::createEnemyPrototype() const {
  return new GenericEnemy();
}
