#pragma once

class EnemyStats {
public:
  float getDamage() const;
  float getHealth() const;
  float getArmor() const;
  float getSpeed() const;

  // Setters
  void setDamage(float newDamage);
  void setHealth(float newHealth);
  void setArmor(float newArmor);
  void setSpeed(float newSpeed);

private:
  float damage;
  float health;
  float armor;
  float speed;
};
