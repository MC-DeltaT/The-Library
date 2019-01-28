#ifndef TL_TUPLE_TRANSFORM_HPP
#define TL_TUPLE_TRANSFORM_HPP


#include <cstddef>			// std::size_t
#include <tuple>			// std::get, std::tuple, std::tuple_element_t, std::tuple_size_v
#include <type_traits>		// std::invoke_result_t
#include <utility>			// std::index_sequence, std::make_index_sequence


namespace tl::tuple {

	namespace detail {

		template<class Tuple, typename UnaryOperation, std::size_t... Idx>
		auto transform_impl(Tuple const& tuple, UnaryOperation op, std::index_sequence<Idx...> idx)
		{
			using result_tuple = std::tuple<std::invoke_result_t<UnaryOperation, std::tuple_element_t<Idx, Tuple>>...>;
			using std::get;
			return result_tuple(op(get<Idx>(tuple))...);
		}


		template<class Tuple1, class Tuple2, typename BinaryOperation, std::size_t... Idx>
		auto transform_impl(Tuple1 const& tuple1, Tuple2 const& tuple2, BinaryOperation op, std::index_sequence<Idx...> idx)
		{
			using result_tuple = std::tuple<std::invoke_result_t<BinaryOperation, std::tuple_element_t<Idx, Tuple1>, std::tuple_element_t<Idx, Tuple2>>...>;
			using std::get;
			return result_tuple(op(get<Idx>(tuple1), get<Idx>(tuple2))...);
		}

	}


	/* Transforms each element of a tuple with a function and returns the results in a new tuple.
		Works for any tuple type supported by std::get, std::tuple_element and std::tuple_size, but the return type is always std::tuple. */
	template<class Tuple, typename UnaryOperation>
	auto transform(Tuple const& tuple, UnaryOperation op)
	{
		return detail::transform_impl(tuple, op, std::make_index_sequence<std::tuple_size_v<Tuple>>());
	}


	/* Transforms each corresponding pair of elements of two tuples with a function and returns the results in a new tuple.
		The two tuples must have the same number of elements.
		Works for any tuple types supported by std::get, std::tuple_element and std::tuple_size, but the return type is always std::tuple. */
	template<class Tuple1, class Tuple2, typename BinaryOperation>
	auto transform(Tuple1 const& tuple1, Tuple2 const& tuple2, BinaryOperation op)
	{
		return detail::transform_impl(tuple1, tuple2, op, std::make_index_sequence<std::tuple_size_v<Tuple1>>());
	}

}


#endif
