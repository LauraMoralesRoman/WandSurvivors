#include "Player.hpp"
#include "entities/PlayerStat.hpp"
#include "gameContext.hpp"
#include "input_manager/PubSubSystem.hpp"
#include <algorithm>
#include <vector>

void Player::update(game::Context& ctx) {
	
}

void Player::start(game::Context& ctx) {
	auto& pubsub = input_manager::pubSub::PubSubSystem::getInstance();

	// TODO: add delta time
	pubsub.subscribe(input_manager::inputSystem::ActionType::MOVE_UP, [this]() {
		this->actualPosition.y -= 10.0f;
	});

	pubsub.subscribe(input_manager::inputSystem::ActionType::MOVE_DOWN, [this]() {
		this->actualPosition.y += 10.0f;
	});

	pubsub.subscribe(input_manager::inputSystem::ActionType::MOVE_LEFT, [this]() {
		this->actualPosition.x -= 10.0f;
	});

	pubsub.subscribe(input_manager::inputSystem::ActionType::MOVE_RIGHT, [this]() {
		this->actualPosition.x += 10.0f;
	});
}

// /////////////////
// Utility functions
// /////////////////

Vector2 Player::getActualPosition() const { return actualPosition; }

Player& Player::setActualPosition(Vector2 newPosition) {
  actualPosition = newPosition;
	return *this;
}

Player& Player::setWands(const std::vector<Wand>& wands) {
	this->wands = wands;
	return *this;
}

Player& Player::setStats(const PlayerStat& stats) {
	this->stats = stats;
	return *this;
}

const PlayerStat& Player::getPlayerStats() const { return stats; }
const std::vector<Wand>& Player::getPlayerWands() const { return wands; }

void Player::addNewWand(const Wand &wand) { wands.emplace_back(wand); }

void Player::deleteWand(const Wand& wand) {
	const auto& iter = std::find(wands.begin(), wands.end(), wand);
	if (iter != wands.end()) {
		wands.erase(iter);
	}
}
// void Player::deleteWand(Wand &wand) { wands.remove(wand); }

void Player::upgradeHealth() {
	stats.health += 5.0f;
}

void Player::upgradeArmor() {
	stats.armor += 2.0f;
}

void Player::upgradeSpeed() {
	stats.speed += 1.0f;
}
