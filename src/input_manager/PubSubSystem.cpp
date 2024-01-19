#include "PubSubSystem.hpp"
#include "InputSystem.hpp"

namespace input_manager::pubSub {

PubSubSystem &PubSubSystem::getInstance() {
  static PubSubSystem instance;
  return instance;
}

bool PubSubSystem::exists(inputSystem::ActionType action) {
  auto it = topics.find(action);
  return (it != topics.end());
}

PubSubSystem::FunGetTopicErr
PubSubSystem::getTopic(inputSystem::ActionType action) {
  auto it = topics.find(action);
  if (it != topics.end()) {
    return FunGetTopicErr(it->second);
  }

  else {
    return FunGetTopicErr("Topic not created");
  }
}

void PubSubSystem::subscribe(inputSystem::ActionType action,
                             Callback callback) {
  auto &instance = getInstance();
  auto &topic = instance.topics[action];
  topic.push_back(callback);
}

void PubSubSystem::publish(inputSystem::ActionType action) {
  auto it = this->topics.find(action);

  if (it != this->topics.end() && !this->muted) {
    auto &vect = it->second;

    for (const auto &func : vect) {
      func();
    }
  }
}

void PubSubSystem::mute() {
  auto &instance = getInstance();
  instance.muted = true;
}

void PubSubSystem::unmute() {
  auto &instance = getInstance();
  instance.muted = false;
}

} // namespace input_manager::pubSub
