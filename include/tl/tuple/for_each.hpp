#ifndef TL_TUPLE_FOR_EACH_HPP
#define TL_TUPLE_FOR_EACH_HPP


#include <cstddef>		// std::size_t
#include <tuple>		// std::get, std::tuple_size_v
#include <utility>		// std::index_sequence, std::make_index_sequence


namespace tl::tuple {

	namespace detail {

		template<class Tuple, typename UnaryFunction, std::size_t... Idx>
		void for_each_impl(Tuple& tuple, UnaryFunction func, std::index_sequence<Idx...> idx)
		{
			using std::get;
			(func(get<Idx>(tuple)), ...);
		}

	}


	/* Applies a function to each element of a tuple.
		Works for any tuple type supported by std::get and std::tuple_size. */
	template<class Tuple, typename UnaryFunction>
	void for_each(Tuple& tuple, UnaryFunction func)
	{
		detail::for_each_impl(tuple, func, std::make_index_sequence<std::tuple_size_v<Tuple>>());
	}

}


#endif
