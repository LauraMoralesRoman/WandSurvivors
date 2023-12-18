#pragma once

#include "components/entity.hpp"
#include "components/module.hpp"
#include "defs.hpp"

#include <algorithm>
#include <vector>

namespace core::components {
	template<typename C>
	class EntityManager {
		public:
			EntityManager(Module<C>& mod)
				: module(mod) {
			}

			Entity<C>& create_instance() {
				auto instance = self->module.instantiate();
				Entity<C> entity; 
				entity.swap(instance);
				self->instances.push_back(std::move(entity));
				return self->instances.back();
			}

			decltype(auto) size() {
				return self->instances.size();
			}

			decltype(auto) remove_marked() {
				auto prev_len = self->instances.size();
				self->instances.erase(std::remove_if(
					self->instances.begin(),
					self->instances.end(),
					[](auto& instance) { return instance.is_marked(); }
				), self->instances.end());

				return prev_len - self->instances.size();
			}

		private:
			std::vector<Entity<C>> instances;
			Module<C> module;
	};
}
