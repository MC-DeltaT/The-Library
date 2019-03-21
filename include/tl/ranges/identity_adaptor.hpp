#ifndef TL_RANGES_IDENTITY_ADAPTOR_HPP
#define TL_RANGES_IDENTITY_ADAPTOR_HPP


#include <iterator>			// std::begin, std::end

#include <tl/ranges/adaptor_base.hpp>		// tl::ranges::adaptor_base


namespace tl::ranges {

	// Range adaptor that does not apply any transformations.
	template<class Range>
	class identity_adaptor : public adaptor_base<identity_adaptor<Range>> {
	public:
		/* Special members */

		// Destructs the base range.
		~identity_adaptor() = default;

		// Value-initializes the base range.
		identity_adaptor() :
			_base()
		{}

		// Copy-constructs the base range from that of other.
		identity_adaptor(identity_adaptor const& other) = default;

		// Move-constructs the base range from that of other.
		identity_adaptor(identity_adaptor&& other) = default;

		// Constructs the base range from the given value.
		identity_adaptor(Range base) :
			_base(base)
		{}


		/* Operators */

		// Copy-assigns the base range from that of rhs.
		identity_adaptor& operator=(identity_adaptor const& rhs) = default;

		// Move-assigns the base range from that of rhs.
		identity_adaptor& operator=(identity_adaptor&& rhs) = default;


		/* General functions */

		// Gets the base range.
		Range const& base() const
		{
			return _base;
		}


	protected:
		/* General functions */

		// Gets a (const) iterator to the start of r's base range.
		template<class IdentityAdaptor>
		static auto _begin(IdentityAdaptor& r)
		{
			return std::begin(r._base);
		}

		// Gets a (const) sentinel to the end of r's base range.
		template<class IdentityAdaptor>
		static auto _end(IdentityAdaptor& r)
		{
			return std::end(r._base);
		}


	private:
		/* Variables */

		Range _base;
	};

}


#endif
