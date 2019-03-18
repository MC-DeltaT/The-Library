#ifndef TL_RANGES_REVERSING_ADAPTOR_HPP
#define TL_RANGES_REVERSING_ADAPTOR_HPP


#include <iterator>			// std::begin, std::end, std::reverse_iterator

#include <tl/ranges/adaptor_base.hpp>		// tl::ranges::adaptor_base


namespace tl::ranges {

	// Range adaptor that reverses the order of elements.
	template<class Range>
	class reversing_adaptor : public adaptor_base<reversing_adaptor<Range>> {
	public:
		/* Member types */

		using range_type = Range;


		/* Special members */

		// Destructs the base range.
		~reversing_adaptor() = default;

		// Value-initializes the base range.
		reversing_adaptor() :
			_range()
		{}

		// Copy-constructs the base range from that of other.
		reversing_adaptor(reversing_adaptor const& other) = default;

		// Move-constructs the base range from that of other.
		reversing_adaptor(reversing_adaptor&& other) = default;

		// Constructs the base range from the given value.
		explicit reversing_adaptor(Range base) :
			_base(base)
		{}


		/* Operators */

		// Copy-assigns the base range from that of rhs.
		reversing_adaptor& operator=(reversing_adaptor const& rhs) = default;

		// Move-assigns the base range from that of rhs.
		reversing_adaptor& operator=(reversing_adaptor&& rhs) = default;


		/* General functions */

		// Gets the base range.
		Range const& base() const
		{
			return _base;
		}


	protected:
		/* General functions */

		// Gets a (const) iterator to the start of the transformed range denoted by the reversing_adaptor r.
		template<class ReversingAdaptor>
		static auto _begin(ReversingAdaptor& r)
		{
			return std::reverse_iterator(std::end(r._base));
		}

		// Gets a (const) sentinel to the end of the transformed range denoted by the reversing_adaptor r.
		template<class ReversingAdaptor>
		static auto _end(ReversingAdaptor& r)
		{
			return std::reverse_iterator(std::begin(r._base));
		}


	private:
		/* Variables */

		Range _base;
	};

}


#endif
