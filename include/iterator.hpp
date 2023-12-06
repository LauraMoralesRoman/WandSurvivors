#pragma once

#include <ranges>
#include <concepts>

// Define a range concept with a specified value type
template <typename Range, typename ValueType>
concept RangeWithType = requires(Range range) {
    requires std::ranges::range<Range>;
    requires std::same_as<std::ranges::range_value_t<Range>, ValueType>;
};
