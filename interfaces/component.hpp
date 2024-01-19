#pragma once

#include "gameContext.hpp"
using VTable = int*;

class Component {
	public:
		virtual void update(game::Context& ctx) = 0;
		virtual void start(game::Context& ctx) = 0;
		virtual ~Component() {}
};


extern "C" Component* instantiate();
