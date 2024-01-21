#include "../../include/raylib.h"
#include "PlayerStat.hpp"
#include "UpgradePlayerStats.hpp"
#include "Wand.hpp"
#include "component.hpp"
#include <vector>
#pragma once

class Player : virtual public UpgradePlayerStats, virtual public Component {
public:
  Player() = default;

  Vector2 getActualPosition() const;
  Player &setActualPosition(Vector2 newPosition);

  Player &setStats(const PlayerStat &stats);
  const PlayerStat &getPlayerStats() const;

  // upgrade stats
  void upgradeHealth() override;
  void upgradeArmor() override;
  void upgradeSpeed() override;

  std::vector<Wand> &getPlayerWands();
  void addNewWand(const Wand &wand);
  void deleteWand(const Wand &wand);
  Player &setWands(const std::vector<Wand> &wands);

  // Component system
  void update(game::Context &ctx) override;
  void start(game::Context &ctx) override;

private:
  Vector2 actualPosition;
  PlayerStat stats;
  std::vector<Wand> wands{};
};
