#pragma once

enum class WandType { FIRE, ICE, WATER, WIND };

class WandStat {
public:
  WandStat(float initialDamage, WandType initialType)
      : damage(initialDamage), type(initialType) {}

  float getDamage() const;
  void setDamage(float newDamage);

  WandType getType() const;

private:
  float damage;
  WandType type;
};
