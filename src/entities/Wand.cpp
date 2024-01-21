#include "Wand.hpp"

WandStat &Wand::getWandStats() { return stats; }

Spell &Wand::getSpell() { return spell; }

void Wand::setWandStats(WandStat &newStats) { stats = newStats; }

void Wand::castSpell(Vector2 origin, Vector2 destination) {
  Vector2 direction = Vector2Subtract(destination, origin);
  direction = Vector2Normalize(direction);

  float spellSpeed = 10.0f; // Ajusta la velocidad según tus necesidades

  // Puedes ajustar la dirección o velocidad según tus necesidades
  spell.setSpeed(Vector2Scale(direction, spellSpeed));
}
