#include "system.hpp"
#include "utils/metafunctions.hpp"
#include <algorithm>
#include <tuple>
#include <type_traits>
#include <utility>

#include <inotifytools/inotifytools.h>

void core::components::GameEntityManager::remove_marked() {
	metafunc::for_each_in_tuple(self->specific_managers, [](auto& manager) {
		manager.remove_marked();
	});
}

namespace metafunc {
	template<typename F, class List>
	struct TypeFunctionMapping;

	struct NullResult {};

	template<typename In>
	struct VoidToNull {
		using type = In;
	};

	template<>
	struct VoidToNull<void> {
		using type = NullResult;
	};

	template<typename T, typename Tuple>
	struct PrepentTypeToTuple;

	template<typename T, typename... Types>
	struct PrepentTypeToTuple<T, std::tuple<Types...>> {
		using type = std::tuple<T, Types...>;
	};

	template<typename Tuple>
	struct FilterNullResultsFromTuple;

	template<typename Head, typename... Body>
	struct FilterNullResultsFromTuple<std::tuple<Head, Body...>> {
		using type = PrepentTypeToTuple<Head, typename FilterNullResultsFromTuple<std::tuple<Body...>>::type>::type;
	};

	template<typename... Body>
	struct FilterNullResultsFromTuple<std::tuple<NullResult, Body...>> {
		using type = FilterNullResultsFromTuple<std::tuple<Body...>>::type;
	};

	template<>
	struct FilterNullResultsFromTuple<std::tuple<>> {
		using type = std::tuple<>;
	};

	// Base case for recursion: no more arguments, return an empty tuple
	constexpr std::tuple<> filter_tuple() {
		return {};
	}

	// Recursive case: head is not NullResult
	template <typename Head, typename... Tail>
	constexpr auto filter_tuple(Head&& head, Tail&&... tail) {
		if constexpr (std::is_same_v<std::decay_t<Head>, NullResult>) {
			return filter_tuple(std::forward<Tail>(tail)...);
		} else {
			return std::tuple_cat(
				std::make_tuple(std::forward<Head>(head)),
				filter_tuple(std::forward<Tail>(tail)...)
			);
		}
	}

	template <typename... Args>
	decltype(auto) filtered_make_tuple(Args&&... args) {
		return filter_tuple(std::forward<Args>(args)...);
	}

	template<typename F, typename... Types, template <typename...> class List>
	struct TypeFunctionMapping<F, List<Types...>> {
		TypeFunctionMapping(const F& func)
			: result(filtered_make_tuple (
			([&func]() {
			 	if constexpr (std::is_void_v<decltype(std::declval<F>().template operator()<Types>())>) {
					func.template operator()<Types>();
					return NullResult{};
				} else {
					return func.template operator()<Types>();
				}
			 })()...
		)) {}
		FilterNullResultsFromTuple<std::tuple<typename VoidToNull<decltype(std::declval<F>().template operator()<Types>())>::type...>>::type result;
	};

	// Helper functions
	template <typename List>
	constexpr decltype(auto) type_function_map(const auto& func) {
		return TypeFunctionMapping<decltype(func), List>{std::move(func)}.result;
	}
}

core::components::GameEntityManager::GameEntityManager() 
	: BaseType(EntityModules{}) {
	
	// Generate observers
	auto result = ::metafunc::type_function_map<std::tuple<int, float>>([]<typename T>() {
	});
}
