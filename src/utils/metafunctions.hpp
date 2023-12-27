#pragma once

#include <tuple>

namespace core::metafunc {
	// Type lists
	template<typename... Types>
	struct TypeList {};

	template <typename List, template<typename...> class Target>
	struct ApplyListToType {};

	template<typename... Types, template<typename...> class Target>
	struct ApplyListToType<TypeList<Types...>, Target> {
		using type = Target<Types...>;
	};

	template<typename T, template<typename> class Morphism>
	struct TransformTuple;

	template<typename... Types, template<typename> class Morphism>
	struct TransformTuple<std::tuple<Types...>, Morphism> {
		using type = std::tuple<typename Morphism<Types>::type...>;
	};

	// Process each element in the tuple
	template<typename Tuple, typename Func, std::size_t... Indices>
	void for_each_in_tuple_impl(Tuple&& t, Func f, std::index_sequence<Indices...>) {
		// Using a fold-expression to call f on each element of the tuple
		(..., f(std::get<Indices>(std::forward<Tuple>(t))));
	}

	// Public interface that users can call
	template<typename Tuple, typename Func>
	void for_each_in_tuple(Tuple&& t, Func f) {
		constexpr std::size_t N = std::tuple_size_v<std::remove_reference_t<Tuple>>;
		for_each_in_tuple_impl(std::forward<Tuple>(t), f, std::make_index_sequence<N>{});
	}
	//
	// Helper functions
	template<typename T, typename... List>
	struct is_in_list;

	template<typename... Types, typename T>
	struct is_in_list<T, TypeList<Types...>> : 
		is_in_list<T, Types...>::type {};

	// Specialization for empty list
	template<typename T>
	struct is_in_list<T> : std::false_type {};

	// Specialization for non-empty list
	template<typename T, typename Head, typename... Tail>
	struct is_in_list<T, Head, Tail...> : std::conditional<
		std::is_same<T, Head>::value,
		std::true_type,
		is_in_list<T, Tail...>
	>::type {};

	// Helper variable template for easier usage
	template<typename T, typename... List>
	inline constexpr bool is_in_list_v = is_in_list<T, List...>::value;

	////////////////////////////////////////////////
	// Utility functions for another metafunctions /
	////////////////////////////////////////////////
	template<typename... Types>
	struct all_true;

	// Base case: no types left, return true
	template<>
	struct all_true<> : std::true_type {};

	// Recursive case
	template<typename Head, typename... Tail>
	struct all_true<Head, Tail...>
		: std::conditional_t<Head::value, all_true<Tail...>, std::false_type> {};

	// Helper variable template
	template<typename... Types>
	inline constexpr bool all_true_v = all_true<Types...>::value;
	
	template<typename... Types>
	struct any_true;

	// Base case: no types left, return false
	template<>
	struct any_true<> : std::false_type {};

	// Recursive case
	template<typename Head, typename... Tail>
	struct any_true<Head, Tail...>
		: std::conditional_t<Head::value, std::true_type, any_true<Tail...>> {};

	// Helper variable template
	template<typename... Types>
	inline constexpr bool any_true_v = any_true<Types...>::value;
}
