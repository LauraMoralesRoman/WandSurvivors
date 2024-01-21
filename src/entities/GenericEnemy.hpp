#include "Enemy.hpp"
#include "EnemyPrototype.hpp"
#include "EnemyStats.hpp"

class GenericEnemy : public virtual Enemy {
public:
  // constructor
  GenericEnemy() = default;

  // functions
  void move(Player &player) override;
  void draw() override;

  std::shared_ptr<EnemyPrototype> clone() const override;

  float makeDamage() const override;
  void takeDamage(float damage) override;
  // getters and setters
  const EnemyStats getStats() const;
  const Vector2 getPosition() const;
  void setPosition(Vector2 newPosition);

private:
  Vector2 position;
  EnemyStats stats = {8.0f, 15.0f, 4.0f, 5.0f};
};
