#ifndef TL_RANGES_ZIPPING_RANGE_HPP
#define TL_RANGES_ZIPPING_RANGE_HPP


#include <iterator>			// std::begin, std::end
#include <tuple>			// std::tuple

#include <tl/iterators/zipping_iterator.hpp>	// tl::iterators::zipping_iterator
#include <tl/ranges/adaptor_base.hpp>			// tl::ranges::adaptor_base
#include <tl/tuple/transform.hpp>				// tl::tuple::transform


namespace tl::ranges {

	// Range adaptor that zips multiple ranges into a single range of tuples.
	template<class... Ranges>
	class zipping_range : public adaptor_base<zipping_range<Ranges...>> {
	public:
		/* Special members */

		// Destructs the base ranges.
		~zipping_range() = default;

		// Value-initializes the base ranges.
		zipping_range() :
			_bases()
		{}

		// Copy-constructs the base ranges from those of other.
		zipping_range(zipping_range const& other) = default;

		// Move-constructs the base ranges from those of other.
		zipping_range(zipping_range&& other) = default;

		// Constructs the base ranges from the given values in a parameter pack.
		explicit zipping_range(Ranges... bases) :
			_bases(bases...)
		{}

		// Constructs the base ranges from the given values in a tuple.
		explicit zipping_range(std::tuple<Ranges...> bases) :
			_bases(bases)
		{}


		/* Operators */

		// Copy-assigns the base ranges from those of rhs.
		zipping_range& operator=(zipping_range const& rhs) = default;

		// Move-assigns the base ranges from those of rhs.
		zipping_range& operator=(zipping_range&& rhs) = default;


		/* General functions */

		// Gets a tuple of the base ranges.
		std::tuple<Ranges...> const& base() const
		{
			return _bases;
		}


	protected:
		/* General functions */

		// Gets a (const) iterator to the start of the zipped range.
		template<class ZippingRange>
		static auto _begin(ZippingRange& r)
		{
			return iterators::zipping_iterator(tuple::transform(r._bases, [](auto& base) { return std::begin(base); }));
		}

		// Gets a (const) sentinel to the end of the zipped range.
		template<class ZippingRange>
		static auto _end(ZippingRange& r)
		{
			return iterators::zipping_iterator(tuple::transform(r._bases, [](auto& base) { return std::end(base); }));
		}


	private:
		/* Variables */

		std::tuple<Ranges...> _bases;
	};

}


#endif
