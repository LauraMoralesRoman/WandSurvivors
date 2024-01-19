#include "test_component.hpp"

void GameObject::start(game::Context& ctx) {

}

void GameObject::update(game::Context& ctx) {

}

int GameObject::foo(int a, int b) {
	return a * b;
}

Component* instantiate() {
	return new GameObject();
}
