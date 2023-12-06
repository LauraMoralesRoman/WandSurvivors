#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <SDL2/SDL.h>
#include <unordered_map>

enum class ActionType { MOVE_LEFT, MOVE_RIGHT, MOVE_UP, MOVE_DOWN, ATTACK };

class InputHandler {
public:
  void mapKeyToAction(SDL_KeyCode key, ActionType action);

  void mapMouseToAction(ActionType action);

  bool isActionTriggered(ActionType action) const;

private:
  std::unordered_map<SDL_KeyCode, ActionType> keyMappings;
  std::unordered_map<ActionType, bool> actions;
  bool isMouseLeftClicked = false;
};

#endif
