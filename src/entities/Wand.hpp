#pragma once

#include "WandStat.hpp"
class Wand {
public:
  Wand(int initialWandId, WandStat initialStats)
      : wandId(initialWandId), stats(initialStats) {}

  WandStat getWandStats() const;
  void setWandStats(WandStat newStats);

  bool operator==(const Wand &other) const { return wandId == other.wandId; }

private:
  int wandId;
  WandStat stats;
};
