#include "Player.hpp"
#include "PlayerStat.hpp"
#include "entities/PlayerStat.hpp"
#include "gameContext.hpp"
#include "input_manager/PubSubSystem.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

void Player::update(game::Context &ctx) {}

void Player::start(game::Context &ctx) {
  auto &pubsub = input_manager::pubSub::PubSubSystem::getInstance();

  // TODO: add delta time
  pubsub.subscribe(input_manager::inputSystem::ActionType::MOVE_UP,
                   [this]() { this->actualPosition.y -= 10.0f; });

  pubsub.subscribe(input_manager::inputSystem::ActionType::MOVE_DOWN,
                   [this]() { this->actualPosition.y += 10.0f; });

  pubsub.subscribe(input_manager::inputSystem::ActionType::MOVE_LEFT,
                   [this]() { this->actualPosition.x -= 10.0f; });

  pubsub.subscribe(input_manager::inputSystem::ActionType::MOVE_RIGHT,
                   [this]() { this->actualPosition.x += 10.0f; });
}

// /////////////////
// Utility functions
// /////////////////

Vector2 Player::getActualPosition() const { return actualPosition; }

Player &Player::setActualPosition(Vector2 newPosition) {
  actualPosition = newPosition;
  return *this;
}

Player &Player::setWands(const std::vector<Wand> &wands) {
  this->wands = wands;
  return *this;
}

Player &Player::setStats(const PlayerStat &stats) {
  this->stats = stats;
  return *this;
}

PlayerStat &Player::getPlayerStats() { return stats; }
std::vector<Wand> &Player::getPlayerWands() { return wands; }

void Player::addNewWand(const Wand &wand) { wands.emplace_back(wand); }

void Player::deleteWand(const Wand &wand) {
  const auto &iter = std::find(wands.begin(), wands.end(), wand);
  if (iter != wands.end()) {
    wands.erase(iter);
  }
}
// void Player::deleteWand(Wand &wand) { wands.remove(wand); }

float Player::makeDamage() const { return wands.at(0).getWandStats().damage; }

void Player::takeDamage(float damage) {
  std::cout << "Current health: " << stats.health << std::endl;

  float newHealth = stats.health - (damage - stats.armor);

  stats.health = newHealth;
  std::cout << "New health: " << stats.health << std::endl;
}
