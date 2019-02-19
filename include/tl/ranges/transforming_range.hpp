#ifndef TL_RANGES_TRANSFORMING_RANGE_HPP
#define TL_RANGES_TRANSFORMING_RANGE_HPP


#include <iterator>										// std::begin, std::end
#include <tl/iterators/transforming_iterator.hpp>		// tl::iterators::transforming_iterator
#include <tl/ranges/range_traits.hpp>					// tl::ranges::range_traits


namespace tl::ranges {

	// Range adaptor that transforms elements with a function.
	template<class Range, typename UnaryOperation>
	class transforming_range {
	public:
		/* Member types */

		using range_type = Range;
		using iterator = iterators::transforming_iterator<typename range_traits<Range>::iterator, UnaryOperation>;
		using const_iterator = iterators::transforming_iterator<typename range_traits<Range const>::iterator, UnaryOperation>;
		using sentinel = iterators::transforming_iterator<typename range_traits<Range>::sentinel, UnaryOperation>;
		using const_sentinel = iterators::transforming_iterator<typename range_traits<Range const>::sentinel, UnaryOperation>;


		/* Special members */

		// Destructs the base range and transformer function object.
		~transforming_range() = default;

		// Value-initializes the base range and transformer function object.
		transforming_range() :
			_base(),
			_op()
		{}

		// Copy-constructs the base range and transformer function object from those of other.
		transforming_range(transforming_range const& other) = default;

		// Move-constructs the base range and transformer function object from those of other.
		transforming_range(transforming_range&& other) = default;

		// Constructs the base range and transformer function object from the given values.
		transforming_range(Range base, UnaryOperation op) :
			_base(base),
			_op(op)
		{}


		/* Operators */

		// Copy-assigns the base range and transformer function object from those of rhs.
		transforming_range& operator=(transforming_range const& rhs) = default;

		// Move-assigns the base range and transformer function object from those of rhs.
		transforming_range& operator=(transforming_range&& rhs) = default;


		/* General functions */

		// Gets the base range.
		Range const& base() const
		{
			return _base;
		}

		// Gets an iterator to the start of the transformed range.
		iterator begin()
		{
			return {std::begin(_base), _op};
		}

		// Gets an iterator to the start of the transformed range.
		const_iterator begin() const
		{
			return {std::begin(_base), _op};
		}

		// Gets a sentinel to the end of the transformed range.
		sentinel end()
		{
			return {std::end(_base), _op};
		}

		// Gets a sentinel to the end of the transformed range.
		const_sentinel end() const
		{
			return {std::end(_base), _op};
		}

		// Gets the transformer function.
		UnaryOperation const& operation() const
		{
			return _op;
		}


	private:
		/* Variables */

		Range _base;
		UnaryOperation _op;
	};

}


#endif
