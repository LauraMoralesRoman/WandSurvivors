#include "GenericEnemyFactory.hpp"

std::shared_ptr<EnemyPrototype>
GenericEnemyFactory::createEnemyPrototype() const {

  std::shared_ptr<EnemyPrototype> prototype = std::make_shared<GenericEnemy>();
  return prototype;
}
