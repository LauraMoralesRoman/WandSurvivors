#include "UpgradeShop.hpp"

const Vector2 UpgradeShop::getPosition() const { return position; }

void UpgradeShop::setPosition(Vector2 newPosition) { position = newPosition; }

const float UpgradeShop::getHeight() const { return height; }

const float UpgradeShop::getWidth() const { return width; }

void UpgradeShop::draw() {
  DrawRectangleV(position, Vector2{height, width}, color);
}

void UpgradeShop::isInside(Vector2 center, float radius) {
  Rectangle rec;
  rec.x = position.x;
  rec.y = position.y;
  rec.height = height;
  rec.width = width;
  hasPlayer = CheckCollisionCircleRec(center, radius, rec);
}

bool UpgradeShop::isPlayerInside() { return hasPlayer; }

Color UpgradeShop::getColor() const { return color; }
