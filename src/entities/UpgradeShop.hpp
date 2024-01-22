#pragma once
#include "../../include/raylib.h"
class UpgradeShop {
public:
  UpgradeShop(Vector2 initPosition, float initHeight, float initWidth,
              Color iColor)
      : position(initPosition), height(initHeight), width(initWidth),
        color(iColor) {}

  const Vector2 getPosition() const;
  void setPosition(Vector2 newPosition);

  const float getHeight() const;
  const float getWidth() const;
  bool isPlayerInside();
  void draw();
  void isInside(Vector2 center, float radius);
  Color getColor() const;

private:
  Vector2 position;
  float height;
  float width;
  Color color;
  bool hasPlayer = false;
};
