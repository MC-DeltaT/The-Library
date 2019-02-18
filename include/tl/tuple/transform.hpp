#ifndef TL_TUPLE_TRANSFORM_HPP
#define TL_TUPLE_TRANSFORM_HPP


#include <cstddef>								// std::size_t
#include <tl/type_support/remove_cvref.hpp>		// tl::type_support::remove_cvref_t
#include <tuple>								// std::get, std::tuple, std::tuple_size_v
#include <type_traits>							// std::invoke_result_t
#include <utility>								// std::forward, std::index_sequence, std::make_index_sequence


namespace tl::tuple {

	namespace detail {

		template<class Tuple, typename UnaryOperation, std::size_t... Idx>
		auto transform_impl(Tuple&& tuple, UnaryOperation op, std::index_sequence<Idx...> idx)
		{
			using std::get;
			using result_tuple = std::tuple<std::invoke_result_t<UnaryOperation, decltype(get<Idx>(std::forward<Tuple>(tuple)))>...>;
			return result_tuple(op(get<Idx>(std::forward<Tuple>(tuple)))...);
		}


		template<class Tuple1, class Tuple2, typename BinaryOperation, std::size_t... Idx>
		auto transform_impl(Tuple1&& tuple1, Tuple2&& tuple2, BinaryOperation op, std::index_sequence<Idx...> idx)
		{
			using std::get;
			using result_tuple = std::tuple<std::invoke_result_t<BinaryOperation,
				decltype(get<Idx>(std::forward<Tuple1>(tuple1))), decltype(get<Idx>(std::forward<Tuple2>(tuple2)))>...>;
			return result_tuple(op(get<Idx>(std::forward<Tuple1>(tuple1)), get<Idx>(std::forward<Tuple2>(tuple2)))...);
		}

	}


	/* Transforms each element of a tuple with a function and returns the results in a new tuple.
		Works for any tuple type supported by std::get, std::tuple_element and std::tuple_size, but the return type is always std::tuple. */
	template<class Tuple, typename UnaryOperation>
	auto transform(Tuple&& tuple, UnaryOperation op)
	{
		constexpr static auto idx = std::make_index_sequence<std::tuple_size_v<type_support::remove_cvref_t<Tuple>>>();
		return detail::transform_impl(std::forward<Tuple>(tuple), op, idx);
	}


	/* Transforms each corresponding pair of elements of two tuples with a function and returns the results in a new tuple.
		The two tuples must have the same number of elements.
		Works for any tuple types supported by std::get, std::tuple_element and std::tuple_size, but the return type is always std::tuple. */
	template<class Tuple1, class Tuple2, typename BinaryOperation>
	auto transform(Tuple1&& tuple1, Tuple2&& tuple2, BinaryOperation op)
	{
		constexpr static auto idx = std::make_index_sequence<std::tuple_size_v<type_support::remove_cvref_t<Tuple1>>>();
		return detail::transform_impl(std::forward<Tuple1>(tuple1), std::forward<Tuple2>(tuple2), op, idx);
	}

}


#endif
