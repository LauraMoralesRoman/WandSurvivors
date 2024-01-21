#include "Enemy.hpp"
#include "EnemyPrototype.hpp"
#include "EnemyStats.hpp"

class GenericEnemy : public Enemy {
public:
  // constructor
  GenericEnemy() = default;

  // functions
  void attack() const override;
  void move(Player &player) override;
  void draw() override;

  EnemyPrototype *clone() const override;

  // getters and setters
  const EnemyStats getStats() const;
  const Vector2 getPosition() const;
  void setPosition(Vector2 newPosition);

private:
  Vector2 position;
  EnemyStats stats;
};
