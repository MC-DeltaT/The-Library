#ifndef TL_RANGES_ITERATOR_RANGE_HPP
#define TL_RANGES_ITERATOR_RANGE_HPP


#include <cstddef>						// std::size_t
#include <iterator>						// std::begin, std::end
#include <tl/ranges/range_traits.hpp>	// tl::ranges::range_traits


namespace tl::ranges {

	/* Range that stores a begin iterator and end sentinel.
		Useful to create a non-owning view of a container. */
	template<typename Iterator, typename Sentinel = Iterator>
	class iterator_range {
	public:
		/* Special members */

		// Destructs the iterator and sentinel.
		~iterator_range() = default;

		// Value-initializes the iterator and sentinel.
		iterator_range() :
			_begin(),
			_end()
		{}

		// Copy-constructs the iterator and sentinel from those of other.
		iterator_range(iterator_range const& other) = default;

		// Move-constructs the iterator and sentinel from those of other.
		iterator_range(iterator_range&& other) = default;

		// Constructs the iterator and sentinel from the given values.
		iterator_range(Iterator begin, Sentinel end) :
			_begin(begin),
			_end(end)
		{}

		// Constructs the iterator and sentinel from the begin and end of a range.
		template<class Range>
		explicit iterator_range(Range& range) :
			_begin(std::begin(range)),
			_end(std::end(range))
		{}


		/* Operators */

		// Copy-assigns the iterator and sentinel from those of rhs.
		iterator_range& operator=(iterator_range const& rhs) = default;

		// Move-assigns the iterator and sentinel from those of rhs.
		iterator_range& operator=(iterator_range&& rhs) = default;


		/* General functions */

		// Returns the iterator.
		Iterator begin() const
		{
			return _begin;
		}

		// Returns the sentinel.
		Sentinel end() const
		{
			return _end;
		}


	private:
		/* Variables */

		Iterator _begin;
		Sentinel _end;
	};


	template<class Range>
	explicit iterator_range(Range&) -> iterator_range<typename range_traits<Range>::iterator, typename range_traits<Range>::sentinel>;

	template<typename T, std::size_t N>
	explicit iterator_range(T(&)[N]) -> iterator_range<T*>;

}


#endif
