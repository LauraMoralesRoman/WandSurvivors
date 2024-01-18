#pragma once

class PlayerStat {
public:
  PlayerStat(float initialHealth, float initialArmor, float initialSpeed)
      : health(initialHealth), armor(initialArmor), speed(initialSpeed) {}

  // getters and setters
  float getHealth() const { return health; }
  void setHealth(float newHealth) { health = newHealth; }

  float getArmor() const { return armor; }
  void setArmor(float newArmor) { armor = newArmor; }

  float getSpeed() const { return speed; }
  void setSpeed(float newSpeed) { speed = newSpeed; }

private:
  float health;
  float armor;
  float speed;
};
