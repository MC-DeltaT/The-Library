#ifndef TL_TUPLE_FOLDL_HPP
#define TL_TUPLE_FOLDL_HPP


#include <cstddef>		// std::size_t
#include <tuple>		// std::get, std::tuple_size_v


namespace tl::tuple {

	namespace detail {

		template<std::size_t Idx, class Tuple, typename BinaryOperation, typename T>
		auto foldl_impl(Tuple const& tuple, BinaryOperation op, T acc)
		{
			if constexpr (Idx == std::tuple_size_v<Tuple>) {
				return acc;
			}
			else {
				using std::get;
				return foldl_impl<Idx + 1>(tuple, op, op(acc, get<Idx>(tuple)));
			}
		}

	}


	/* Performs a left fold on a tuple over a binary function.
		The tuple must have at least one element.
		Works with any tuple type that is supported by std::get and std::tuple_size. */
	template<class Tuple, typename BinaryOperation>
	auto foldl(Tuple const& tuple, BinaryOperation op)
	{
		using std::get;
		return detail::foldl_impl<1>(tuple, op, get<0>(tuple));
	}


	/* Performs a left fold on a tuple over a binary function, using the specified initial value.
		Works with any tuple type that is supported by std::get and std::tuple_size. */
	template<class Tuple, typename BinaryOperation, typename T>
	auto foldl(Tuple const& tuple, BinaryOperation op, T init)
	{
		return detail::foldl_impl<0>(tuple, op, init);
	}

}


#endif
