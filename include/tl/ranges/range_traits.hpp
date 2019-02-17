#ifndef TL_RANGES_RANGE_TRAITS_HPP
#define TL_RANGES_RANGE_TRAITS_HPP


#include <iterator>			// std::begin, std::end, std::iterator_traits
#include <utility>			// std::declval


namespace tl::ranges {

	// Provides the type traits of a range type.
	template<typename Range>
	struct range_traits {
		using iterator = decltype(std::begin(std::declval<Range&>()));
		using sentinel = decltype(std::end(std::declval<Range&>()));
		using value_type = typename std::iterator_traits<iterator>::value_type;
		using reference = typename std::iterator_traits<iterator>::reference;
	};

}


#endif
