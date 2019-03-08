#ifndef TL_RANGES_COMBINING_RANGE_HPP
#define TL_RANGES_COMBINING_RANGE_HPP


#include <iterator>			// std::begin, std::end
#include <tuple>			// std::tuple

#include <tl/iterators/combining_iterator.hpp>		// tl::iterators::combining_iterator
#include <tl/ranges/range_traits.hpp>				// tl::ranges::range_traits
#include <tl/tuple/transform.hpp>					// tl::tuple::transform


namespace tl::ranges {

	// Range adaptor that combines multiple ranges' corresponding elements with a function.
	template<typename Operation, class... Ranges>
	class combining_range {
	public:
		/* Member types */

		using iterator = iterators::combining_iterator<Operation, typename range_traits<Ranges>::iterator...>;
		using const_iterator = iterators::combining_iterator<Operation, typename range_traits<Ranges const>::iterator...>;
		using sentinel = iterators::combining_iterator<Operation, typename range_traits<Ranges>::sentinel...>;
		using const_sentinel = iterators::combining_iterator<Operation, typename range_traits<Ranges const>::sentinel...>;


		/* Special members */

		// Destructs the base ranges and combiner function object.
		~combining_range() = default;

		// Value-initializes the base ranges and combiner function object.
		combining_range() :
			_bases(),
			_op()
		{}

		// Copy-constructs the base ranges and combiner function object from those of other.
		combining_range(combining_range const& other) = default;

		// Move-constructs the base ranges and combiner function object from those of other.
		combining_range(combining_range&& other) = default;

		// Constructs the base ranges and combiner function object from the given values.
		explicit combining_range(Operation op, Ranges... bases) :
			_bases(bases...),
			_op(op)
		{}

		// Constructs the base ranges and combiner function object from the given values.
		combining_range(Operation op, std::tuple<Ranges...> bases) :
			_bases(bases),
			_op(op)
		{}


		/* Operators */

		// Copy-assigns the base ranges and combiner function object from those of rhs.
		combining_range& operator=(combining_range const& rhs) = default;

		// Move-assigns the base ranges and combiner function object from those of rhs.
		combining_range& operator=(combining_range&& rhs) = default;


		/* General functions */

		// Gets a tuple of the base ranges.
		std::tuple<Ranges...> const& base() const
		{
			return _bases;
		}

		// Gets an iterator to the start of the adapted range.
		iterator begin()
		{
			return {_op, tuple::transform(_bases, [](auto& r) { return std::begin(r); })};
		}

		// Gets an iterator to the start of the adapted range.
		const_iterator begin() const
		{
			return {_op, tuple::transform(_bases, [](auto const& r) { return std::begin(r); })};
		}

		// Gets a sentinel to the end of the adapted range.
		sentinel end()
		{
			return {_op, tuple::transform(_bases, [](auto& r) { return std::end(r); })};
		}

		// Gets a sentinel to the end of the adapted range.
		const_sentinel end() const
		{
			return {_op, tuple::transform(_bases, [](auto const& r) { return std::end(r); })};
		}

		// Gets the combiner function.
		Operation const& operation() const
		{
			return _op;
		}


	private:
		/* Variables */

		std::tuple<Ranges...> _bases;
		Operation _op;
	};

}


#endif
