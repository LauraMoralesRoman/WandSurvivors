#include "Wand.hpp"
#include <memory>

const WandStat &Wand::getWandStats() const { return stats; }

void Wand::setWandStats(WandStat &newStats) { stats = newStats; }

std::shared_ptr<Spell> Wand::castSpell(Vector2 origin, Vector2 destination) {
  Vector2 direction = Vector2Normalize(Vector2Subtract(destination, origin));

  return std::make_shared<Spell>(origin, direction);
}
