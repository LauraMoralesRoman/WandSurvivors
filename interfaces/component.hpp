#pragma once

using VTable = int*;

class Component {
	virtual void update() = 0;
	virtual void start() = 0;
};


extern "C" Component* instantiate();
