#ifndef TL_ITERATORS_COMBINING_ITERATOR_HPP
#define TL_ITERATORS_COMBINING_ITERATOR_HPP


#include <iterator>		// std::iterator_traits
#include <tuple>		// std::apply, std::tuple

#include <tl/iterators/transforming_iterator.hpp>		// tl::iterators::transforming_iterator
#include <tl/iterators/zipping_iterator.hpp>			// tl::iterators::zipping_iterator
#include <tl/type_support/function_result.hpp>			// tl::type_support::function_result_t


namespace tl::iterators {

	namespace detail {

		/* Creates a combining iterator from a zipping_iterator inside a transforming_iterator, which is then forwarded formally by combining_iterator.
			op is taken and used by reference; the function object itself resides in the wrapping instance of combining_iterator. */
		template<typename Operation, typename... Iterators>
		auto make_combining_iterator_impl(Operation& op, std::tuple<Iterators...> iterators)
		{
			// Need to inject a usage of std::apply to unpack the zipping_iterator's output tuple into arguments for the user-provided combiner function.
			return transforming_iterator(zipping_iterator(iterators), [&op](auto deref_tuple) {
					return std::apply(op, deref_tuple);
				});
		}

		template<typename Operation, typename... Iterators>
		using combining_iterator_impl = type_support::function_result_t<decltype(make_combining_iterator_impl<Operation, Iterators...>)>;

	}


	/* Iterator adaptor that iterates multiple iterators simultaneously and combines the iterates values with a function.
		For simplicity this iterator inherits from tranforming_iterator. Its interface and supported operations are indentical except for the public
		constructs explicitly declared here. */
	template<typename Operation, typename... Iterators>
	class combining_iterator : public detail::combining_iterator_impl<Operation, Iterators...> {
	private:
		// The transforming_iterator type from which this class inherits and which contains the majority of the implementation.
		using _impl_type = detail::combining_iterator_impl<Operation, Iterators...>;

	public:
		/* Special members */

		// Value-initializes the base iterators and combiner function object.
		combining_iterator() :
			_op(),
			_impl_type()
		{}

		// Constructs the base iterators and combiner function object from the given values.
		explicit combining_iterator(Operation op, Iterators... bases) :
			_op(op),
			_impl_type(detail::make_combining_iterator_impl<Operation, Iterators...>(_op, std::tuple<Iterators...>(bases...)))
		{}

		// Constructs the base iterators and combiner function object from the given values.
		combining_iterator(Operation op, std::tuple<Iterators...> bases) :
			_op(op),
			_impl_type(detail::make_combining_iterator_impl<Operation, Iterators...>(_op, bases))
		{}


		/* General functions */

		// Gets a tuple of the base iterators.
		std::tuple<Iterators...> const& base() const
		{
			return static_cast<_impl_type const&>(*this).base().base();
		}

		// Gets the combiner function.
		Operation const& operation() const
		{
			return _op;
		}


	private:
		/* Variables */

		// Need to hold onto the combiner function separately such that it can be reacquired.
		Operation _op;
	};

}


// Specialization for tl::iterators::combining_iterator.
template<typename Operation, typename... Iterators>
struct std::iterator_traits<tl::iterators::combining_iterator<Operation, Iterators...>> {
	using value_type = typename tl::iterators::combining_iterator<Operation, Iterators...>::value_type;
	using reference = typename tl::iterators::combining_iterator<Operation, Iterators...>::reference;
	using pointer = void;
	using difference_type = typename tl::iterators::combining_iterator<Operation, Iterators...>::difference_type;
	using iterator_category = typename tl::iterators::combining_iterator<Operation, Iterators...>::iterator_category;
};


#endif
