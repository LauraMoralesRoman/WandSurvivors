#pragma once
#include <component.hpp>

class GameObject : public virtual Component {
	public:
		virtual void update() override;
		virtual void start() override;
		virtual int suma(int a, int b);
};
