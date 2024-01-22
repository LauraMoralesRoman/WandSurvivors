#include "../../include/raylib.h"
#include "AttackInt.hpp"
#include "PlayerStat.hpp"
#include "Wand.hpp"
#include "component.hpp"
#include <vector>
#pragma once

class Player : virtual public Component, virtual public AttackInt {
public:
  Player() = default;

  Vector2 getActualPosition() const;
  Player &setActualPosition(Vector2 newPosition);

  Player &setStats(const PlayerStat &stats);
  PlayerStat &getPlayerStats();

  std::vector<Wand> &getPlayerWands();
  void addNewWand(const Wand &wand);
  void deleteWand(const Wand &wand);
  Player &setWands(const std::vector<Wand> &wands);

  // Component system
  void update(game::Context &ctx) override;
  void start(game::Context &ctx) override;

  // attack interface
  float makeDamage() const override;
  void takeDamage(float damage) override;

private:
  Vector2 actualPosition;
  PlayerStat stats;
  std::vector<Wand> wands{};
};
