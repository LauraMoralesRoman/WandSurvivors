#include "../input_manager/InputSystem.hpp"
#include "../input_manager/PubSubSystem.hpp"

#pragma once

using namespace input_manager::pubSub;
using namespace input_manager::inputSystem;

class PlayerInputHandler {
public:
  virtual void subscribe(ActionType actiontype,
                         PubSubSystem::Callback callback) = 0;

  virtual void mute() = 0;

  virtual void unmute() = 0;

  virtual ~PlayerInputHandler() {}
};
