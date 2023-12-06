#pragma once

#include "components/components.hpp"
#include "defs.hpp"

#include <memory>
#include <vector>

namespace core::components {
	template <typename C>
	class EntityManager {
		public:
			EntityManager(Module<C> mod)
				: module(mod) {
			}

			std::weak_ptr<C> create_instance() {
				auto new_instance = instances.emplace_back(self->module.instantiate());
			}
		private:
			std::vector<std::shared_ptr<C>> instances;
			Module<C> module;
	};
}
