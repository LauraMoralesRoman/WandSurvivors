#pragma once

class EnemyPrototype {
public:
  virtual EnemyPrototype *clone() const = 0;
  virtual ~EnemyPrototype() = default;
};
