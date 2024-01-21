#pragma once

enum class WandType { FIRE, ICE, WATER, WIND };

struct WandStat {
  float damage;
  WandType type;
};
