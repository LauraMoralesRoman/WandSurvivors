#pragma once

#include "defs.hpp"
#include <memory>

namespace core::components {
	template<typename C>
	class Entity : public std::unique_ptr<C> {
		public:
			void remove() {
				self->marked_for_delete = true;
			}

			decltype(auto) is_marked() {
				return marked_for_delete;
			}

		private:
			bool marked_for_delete = false;
	};
}
