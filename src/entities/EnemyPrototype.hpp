#pragma once

#include <memory>
class EnemyPrototype {
public:
  virtual std::shared_ptr<EnemyPrototype> clone() const = 0;
  virtual ~EnemyPrototype() = default;
};
