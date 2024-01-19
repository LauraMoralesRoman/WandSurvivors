#pragma once
#include "utils/type_map.hpp"
#include <component.hpp>

class GameObject : public virtual Component {
	public:
		void update(game::Context &ctx) override;
		void start(game::Context &ctx) override;
		virtual int foo(int a, int b);
		virtual ~GameObject() {}

		static constexpr core::utils::TypeIndex type_index() {
			return core::utils::type_id_from_name("GameObject");
		}
};
