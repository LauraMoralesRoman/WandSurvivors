#pragma once

#include "defs.hpp"
#include <optional>
#include <type_traits>
#include <unordered_map>

#include "crc.hpp"

namespace core::metafunc {
	template<typename, typename T>
	struct HasTypeIndexFunction : std::false_type {};

	template<typename T>
	struct HasTypeIndexFunction<decltype(T::type_index(), void()), T>
		: std::true_type {};

	template<typename T>
	constexpr bool has_type_index_v = HasTypeIndexFunction<void, T>::value;
}

namespace core::utils {
	using TypeIndex = long long;

	template<typename T>
	TypeIndex get_type_index_flexible() {
		if constexpr (metafunc::has_type_index_v<T>) {
			return T::type_index();
		} else {
			return typeid(T).hash_code();
		}
	}

	template <typename Val>
	class TypeMap {
		public:
			using Result = std::optional<Val>;

			template<typename Key>
			void set(const Val& value) {
				self->inner_map.insert({
					get_type_index_flexible<Key>(),
					value	
				});
			}

			template<typename Key>
			Result get() const {
				auto it = self->inner_map.find(
							get_type_index_flexible<Key>()
						);

				if (it != self->inner_map.end()) {
					return it->second;
				} else {
					return std::nullopt;
				}
			}

		private:
			std::unordered_map<TypeIndex, Val> inner_map;
	};

	constexpr TypeIndex type_id_from_name(const char* name) {
		return COMPILE_TIME_CRC32_STR(name);
	}
}
