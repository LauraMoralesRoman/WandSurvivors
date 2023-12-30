#pragma once

class PlayerStat {
public:
  PlayerStat(float initialHealth, float initialArmor, float initialSpeed)
      : health(initialHealth), armor(initialArmor), speed(initialSpeed) {}

  // getters and setters
  float getHealth() const;
  void setHealth(float newHealth);

  float gerArmor() const;
  void setArmor(float newArmor);

  float getSpeed() const;
  void setSpeed(float newSpeed);

private:
  float health;
  float armor;
  float speed;
};
