#ifndef TL_RANGES_TRANSFORMING_ADAPTOR_HPP
#define TL_RANGES_TRANSFORMING_ADAPTOR_HPP


#include <iterator>			// std::begin, std::end

#include <tl/iterators/transforming_iterator.hpp>		// tl::iterators::transforming_iterator
#include <tl/ranges/adaptor_base.hpp>					// tl::ranges::adaptor_base


namespace tl::ranges {

	// Range adaptor that transforms elements with a function.
	template<class Range, typename UnaryOperation>
	class transforming_adaptor : public adaptor_base<transforming_adaptor<Range, UnaryOperation>> {
	public:
		/* Member types */

		using range_type = Range;


		/* Special members */

		// Destructs the base range and transformer function object.
		~transforming_adaptor() = default;

		// Value-initializes the base range and transformer function object.
		transforming_adaptor() :
			_base(),
			_op()
		{}

		// Copy-constructs the base range and transformer function object from those of other.
		transforming_adaptor(transforming_adaptor const& other) = default;

		// Move-constructs the base range and transformer function object from those of other.
		transforming_adaptor(transforming_adaptor&& other) = default;

		// Constructs the base range and transformer function object from the given values.
		transforming_adaptor(Range base, UnaryOperation op) :
			_base(base),
			_op(op)
		{}


		/* Operators */

		// Copy-assigns the base range and transformer function object from those of rhs.
		transforming_adaptor& operator=(transforming_adaptor const& rhs) = default;

		// Move-assigns the base range and transformer function object from those of rhs.
		transforming_adaptor& operator=(transforming_adaptor&& rhs) = default;


		/* General functions */

		// Gets the base range.
		Range const& base() const
		{
			return _base;
		}

		// Gets the transformer function.
		UnaryOperation const& operation() const
		{
			return _op;
		}


	protected:
		/* General functions */

		// Gets a (const) iterator to the start of the transformed range.
		template<class TransformingAdaptor>
		static auto _begin(TransformingAdaptor& r)
		{
			return iterators::transforming_iterator(std::begin(r._base), r._op);
		}

		// Gets a (const) sentinel to the end of the transformed range.
		template<class TransformingAdaptor>
		static auto _end(TransformingAdaptor& r)
		{
			return iterators::transforming_iterator(std::end(r._base), r._op);
		}


	private:
		/* Variables */

		Range _base;
		UnaryOperation _op;
	};

}


#endif
