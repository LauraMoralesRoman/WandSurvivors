#pragma once

using VTable = int*;

class Component {
	public:
		virtual void update() = 0;
		virtual void start() = 0;
		virtual ~Component() {}
};


extern "C" Component* instantiate();
