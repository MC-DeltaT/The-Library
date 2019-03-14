#ifndef TL_RANGES_ADAPTOR_BASE_HPP
#define TL_RANGES_ADAPTOR_BASE_HPP


namespace tl::ranges {

	namespace detail {

		// Exposes the protected _begin and _end functions of a range that utilises adaptor_base.
		template<class Range>
		struct derived_adaptor_accessor : private Range {
			using Range::_begin;
			using Range::_end;
		};

	}


	/* Implements the basic interface of a range adaptor using CRTP.
		Custom range adaptors may inherit from this type to make implementation (particularly const propagation) easier.
		To use this class, the range adaptor type must provide public or protected static functions _begin and _end,
		which when passed an object of that range adaptor type, return the begin iterator and end sentinel respectively. */
	template<class Range>
	class adaptor_base {
	public:
		/* General functions */

		// Gets an iterator to the start of the adapted range.
		decltype(auto) begin()
		{
			return detail::derived_adaptor_accessor<Range>::_begin(derived());
		}

		// Gets an iterator to the start of the adapted range.
		decltype(auto) begin() const
		{
			return detail::derived_adaptor_accessor<Range>::_begin(derived());
		}

		// Gets a sentinel to the end of the adapted range.
		decltype(auto) end()
		{
			return detail::derived_adaptor_accessor<Range>::_end(derived());
		}

		// Gets a sentinel to the end of the adapted range.
		decltype(auto) end() const
		{
			return detail::derived_adaptor_accessor<Range>::_end(derived());
		}


	private:
		/* General functions */

		// Gets a reference to the derived object.
		Range& derived()
		{
			return static_cast<Range&>(*this);
		}

		// Gets a const reference to the derived object.
		Range const& derived() const
		{
			return static_cast<Range const&>(*this);
		}
	};

}


#endif
