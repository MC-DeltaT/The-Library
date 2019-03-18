#ifndef TL_RANGES_CONST_ADAPTOR_HPP
#define TL_RANGES_CONST_ADAPTOR_HPP


#include <iterator>			// std::cbegin, std::cend

#include <tl/ranges/adaptor_base.hpp>		// tl::ranges::adaptor_base


namespace tl::ranges {

	// Range adaptor that always provides const iterators/sentinels.
	template<class Range>
	class const_adaptor : public adaptor_base<const_adaptor<Range>> {
	public:
		/* Special members */

		// Destructs the base range.
		~const_adaptor() = default;

		// Value-initializes the base range.
		const_adaptor() :
			_base()
		{}

		// Copy constructs the base range from that of other.
		const_adaptor(const_adaptor const& other) = default;

		// Move-constructs the base range from that of other.
		const_adaptor(const_adaptor&& other) = default;

		// Constructs the base range from the given value.
		const_adaptor(Range base) :
			_base(base)
		{}


		/* Operators */

		// Copy-assigns the base range from that of rhs.
		const_adaptor& operator=(const_adaptor const& rhs) = default;

		// Move-assigns the base range from that of rhs.
		const_adaptor& operator=(const_adaptor&& rhs) = default;


		/* General functions */

		// Gets the base range.
		Range const& base() const
		{
			return _base;
		}


	protected:
		/* General functions */

		// Gets a const iterator to the start of the base range.
		template<class ConstAdaptor>
		static auto _begin(ConstAdaptor& r)
		{
			return std::cbegin(r._base);
		}

		// Gets a const sentinel to the end of the base range.
		template<class ConstAdaptor>
		static auto _end(ConstAdaptor& r)
		{
			return std::cend(r._base);
		}


	private:
		/* Variables */

		Range _base;
	};

}


#endif
