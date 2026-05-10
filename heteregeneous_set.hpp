#pragma once

#include <type_traits>
#include <concepts>

template <typename, auto...>
struct remove_impl;

template <auto... Values>
struct heterogeneous_set
{
	template <auto Value>
	using append = heterogeneous_set<Values..., Value>;

	template <auto Value>
	using remove = remove_impl<heterogeneous_set<>, Value, Values...>::type;
};

template <auto lArg, auto rArg>
constexpr bool values_are_the_same_v = []() {
	if constexpr (std::same_as<decltype(lArg), decltype(rArg)>)
		return lArg == rArg;
	else
		return false;
}();

template <typename Accumulated,
			auto ValueToRemove,
			auto FirstValue,
			auto... OtherValues>
struct remove_impl<Accumulated, ValueToRemove, FirstValue, OtherValues...>
{
	using next = std::conditional_t<
		values_are_the_same_v<ValueToRemove, FirstValue>,
		Accumulated,
		typename Accumulated::template append<FirstValue>
	>;

	using type = remove_impl<next, ValueToRemove, OtherValues...>::type;
};

template <typename Accumulated,
			auto ValueToRemove>
struct remove_impl<Accumulated, ValueToRemove>
{
	using type = Accumulated;
};
