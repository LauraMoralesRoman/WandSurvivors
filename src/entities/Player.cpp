#include "Player.hpp"

Vector2 Player::getActualPosition() const { return actualPosition; }

void Player::setActualPosition(Vector2 newPosition) {
  actualPosition = newPosition;
}

PlayerStat Player::getPlayerStats() const { return stats; }

std::list<Wand> Player::getPlayerWands() const { return wands; }

void Player::addNewWand(Wand &wand) { wands.emplace_back(wand); }
void Player::deleteWand(Wand &wand) { wands.remove(wand); }
