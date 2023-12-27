#include "PubSubSystem.hpp"
#include "InputSystem.hpp"

namespace input_manager::pubSub {

bool PubSubSystem::exists(inputSystem::ActionType action) {
  auto it = topics.find(action);
  if (it != topics.end()) {
    return true;
  } else {
    return false;
  }
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
  auto &topic = topics[action];
  topic.push_back(callback);
}

void PubSubSystem::publish(inputSystem::ActionType action) {
  auto it = topics.find(action);

  if (it != topics.end()) {
    auto &vect = it->second;

    for (const auto &func : vect) {
      func();
    }
  }
}

} // namespace input_manager::pubSub
