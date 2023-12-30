#pragma once

#include "WandStat.hpp"
class Wand {
public:
  Wand(WandStat initialStats) : stats(initialStats) {}

  WandStat getWandStats() const;
  void setWandStats(WandStat newStats);

private:
  WandStat stats;
  // TODO: vector<spells>
  // TODO: vector<group>
};
