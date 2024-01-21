#pragma once
#include "Spell.hpp"
#include "UpgradeWandStats.hpp"
#include "WandStat.hpp"
#include "raymath.h"

class Wand {
public:
  Wand(int initialWandId, WandStat initialStats, Spell sp)
      : wandId(initialWandId), stats(initialStats), spell(sp) {}

  const WandStat &getWandStats() const;
  void setWandStats(WandStat &newStats);

  Spell &getSpell();

  void castSpell(Vector2 origin, Vector2 destination);

  bool operator==(const Wand &other) const { return wandId == other.wandId; }

  // void upgradeDamage() override;

private:
  int wandId;
  WandStat stats;
  Spell spell;
};
