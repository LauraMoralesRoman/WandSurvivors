#include "test_component.hpp"

void GameObject::start() {

}

void GameObject::update() {

}

int GameObject::foo(int a, int b) {
	return a * b;
}

Component* instantiate() {
	return new GameObject();
}
