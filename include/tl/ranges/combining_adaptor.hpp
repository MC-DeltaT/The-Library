#ifndef TL_RANGES_COMBINING_ADAPTOR_HPP
#define TL_RANGES_COMBINING_ADAPTOR_HPP


#include <iterator>			// std::begin, std::end
#include <tuple>			// std::tuple

#include <tl/iterators/combining_iterator.hpp>		// tl::iterators::combining_iterator
#include <tl/ranges/adaptor_base.hpp>				// tl::ranges::adaptor_base
#include <tl/tuple/transform.hpp>					// tl::tuple::transform


namespace tl::ranges {

	// Range adaptor that combines multiple ranges' corresponding elements with a function.
	template<typename Operation, class... Ranges>
	class combining_adaptor : public adaptor_base<combining_adaptor<Operation, Ranges...>> {
	public:
		/* Special members */

		// Destructs the base ranges and combiner function object.
		~combining_adaptor() = default;

		// Value-initializes the base ranges and combiner function object.
		combining_adaptor() :
			_bases(),
			_op()
		{}

		// Copy-constructs the base ranges and combiner function object from those of other.
		combining_adaptor(combining_adaptor const& other) = default;

		// Move-constructs the base ranges and combiner function object from those of other.
		combining_adaptor(combining_adaptor&& other) = default;

		// Constructs the base ranges and combiner function object from the given values.
		explicit combining_adaptor(Operation op, Ranges... bases) :
			_bases(bases...),
			_op(op)
		{}

		// Constructs the base ranges and combiner function object from the given values.
		combining_adaptor(Operation op, std::tuple<Ranges...> bases) :
			_bases(bases),
			_op(op)
		{}


		/* Operators */

		// Copy-assigns the base ranges and combiner function object from those of rhs.
		combining_adaptor& operator=(combining_adaptor const& rhs) = default;

		// Move-assigns the base ranges and combiner function object from those of rhs.
		combining_adaptor& operator=(combining_adaptor&& rhs) = default;


		/* General functions */

		// Gets a tuple of the base ranges.
		std::tuple<Ranges...> const& base() const
		{
			return _bases;
		}

		// Gets the combiner function.
		Operation const& operation() const
		{
			return _op;
		}


	protected:
		/* General functions */

		// Gets a (const) iterator to the start of the combined range.
		template<class CombiningRange>
		static auto _begin(CombiningRange& r)
		{
			return iterators::combining_iterator(r._op, tuple::transform(r._bases, [](auto& base) { return std::begin(base); }));
		}

		// Gets a (const) sentinel to the end of the combined range.
		template<class CombiningRange>
		static auto _end(CombiningRange& r)
		{
			return iterators::combining_iterator(r._op, tuple::transform(r._bases, [](auto& base) { return std::end(base); }));
		}


	private:
		/* Variables */

		std::tuple<Ranges...> _bases;
		Operation _op;
	};

}


#endif
