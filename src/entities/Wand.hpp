#pragma once
#include "Spell.hpp"
#include "WandStat.hpp"
#include "raymath.h"
#include <iostream>
#include <memory>
#include <vector>
class Wand {
public:
  Wand(int initialWandId, WandStat initialStats)
      : wandId(initialWandId), stats(initialStats) {}

  const WandStat &getWandStats() const;
  void setWandStats(WandStat &newStats);
  std::shared_ptr<Spell> castSpell(Vector2 origin, Vector2 destination);

  bool operator==(const Wand &other) const { return wandId == other.wandId; }

private:
  int wandId;
  WandStat stats;
};
