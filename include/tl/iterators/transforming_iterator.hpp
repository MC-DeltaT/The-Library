#ifndef TL_ITERATORS_TRANSFORMING_ITERATOR_HPP
#define TL_ITERATORS_TRANSFORMING_ITERATOR_HPP


#include <functional>		// std::invoke
#include <iterator>			// std::iterator_traits
#include <type_traits>		// std::decay_t, std::invoke_result_t


namespace tl::iterators {

	// Iterator adaptor that transforms iterated values with a function.
	template<typename Iterator, typename UnaryOperation>
	class transforming_iterator {
	public:
		/* Member types */

		using iterator_type = Iterator;
		using reference = std::invoke_result_t<UnaryOperation, typename std::iterator_traits<Iterator>::reference>;
		using value_type = std::decay_t<reference>;
		using difference_type = typename std::iterator_traits<Iterator>::difference_type;
		using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;


		/* Special members */

		// Destructs the base iterator and transformer function object.
		~transforming_iterator() = default;

		// Value-initializes the base iterator and transformer function object.
		transforming_iterator() :
			_base(),
			_op()
		{}

		// Copy-constructs the base base iterator and transformer function object from those of other.
		transforming_iterator(transforming_iterator const& other) = default;

		// Move-constructs the base iterator and transformer function object from those of other.
		transforming_iterator(transforming_iterator&& other) = default;

		// Constructs the base iterator and transformer function object from the given values.
		transforming_iterator(Iterator base, UnaryOperation op) :
			_base(base),
			_op(op)
		{}


		/* Operators */

		// Copy-assigns the base iterator and transformer function object from those of rhs.
		transforming_iterator& operator=(transforming_iterator const& rhs) = default;

		// Move-assigns the base iterator and transformer function object from those of rhs.
		transforming_iterator& operator=(transforming_iterator&& rhs) = default;

		// Advances the base iterator by n.
		transforming_iterator& operator+=(difference_type n)
		{
			_base += n;

			return *this;
		}

		// Advances the base iterator by -n.
		transforming_iterator& operator-=(difference_type n)
		{
			_base -= n;

			return *this;
		}

		// Dereferences the base iterator, applies the function, then returns the result.
		reference operator*() const
		{
			return std::invoke(_op, *_base);
		}

		// Dereferences the base iterator at an offset of n, applies the function, then returns the result.
		reference operator[](difference_type n) const
		{
			return std::invoke(_op, _base[n]);
		}

		// Increments the base iterator, then returns the new state.
		transforming_iterator& operator++()
		{
			++_base;

			return *this;
		}

		// Increments the base iterator, then returns the previous state.
		transforming_iterator operator++(int)
		{
			auto tmp = *this;

			operator++();

			return tmp;
		}

		// Decrements the base iterator, then returns the new state.
		transforming_iterator& operator--()
		{
			--_base;

			return *this;
		}

		// Decrements the base iterator, then returns the previous state.
		transforming_iterator operator--(int)
		{
			auto tmp = *this;

			operator--();

			return tmp;
		}


		/* General functions */

		// Gets the base iterator.
		Iterator const& base() const
		{
			return _base;
		}

		// Gets the transformer function.
		UnaryOperation const& operation() const
		{
			return _op;
		}


	private:
		/* Variables */

		Iterator _base;
		UnaryOperation _op;
	};


	// Returns a copy of lhs advanced by rhs.
	template<typename Iterator, typename UnaryOperation>
	transforming_iterator<Iterator, UnaryOperation> operator+(transforming_iterator<Iterator, UnaryOperation> const& lhs,
		typename transforming_iterator<Iterator, UnaryOperation>::difference_type rhs)
	{
		auto tmp = lhs;
		tmp += rhs;

		return tmp;
	}

	// Returns a copy of rhs advanced by lhs.
	template<typename Iterator, typename UnaryOperation>
	transforming_iterator<Iterator, UnaryOperation> operator+(typename transforming_iterator<Iterator, UnaryOperation>::difference_type lhs,
		transforming_iterator<Iterator, UnaryOperation> const& rhs)
	{
		auto tmp = rhs;
		tmp += lhs;

		return tmp;
	}

	// Returns a copy of lhs advanced by -rhs.
	template<typename Iterator, typename UnaryOperation>
	transforming_iterator<Iterator, UnaryOperation> operator-(transforming_iterator<Iterator, UnaryOperation> const& lhs,
		typename transforming_iterator<Iterator, UnaryOperation>::difference_type rhs)
	{
		auto tmp = lhs;
		tmp -= rhs;

		return tmp;
	}

	// The distance between lhs and rhs is the difference between their base iterators.
	template<typename Iterator1, typename UnaryOperation1, typename Iterator2, typename UnaryOperation2>
	auto operator-(transforming_iterator<Iterator1, UnaryOperation1> const& lhs, transforming_iterator<Iterator2, UnaryOperation2> const& rhs)
	{
		return lhs.base() - rhs.base();
	}

	// lhs and rhs are considered equal if their base iterators are equal.
	template<typename Iterator1, typename UnaryOperation1, typename Iterator2, typename UnaryOperation2>
	bool operator==(transforming_iterator<Iterator1, UnaryOperation1> const& lhs, transforming_iterator<Iterator2, UnaryOperation2> const& rhs)
	{
		return lhs.base() == rhs.base();
	}

	// lhs and rhs are considered unequal if their base iterators are unequal.
	template<typename Iterator1, typename UnaryOperation1, typename Iterator2, typename UnaryOperation2>
	bool operator!=(transforming_iterator<Iterator1, UnaryOperation1> const& lhs, transforming_iterator<Iterator2, UnaryOperation2> const& rhs)
	{
		return lhs.base() != rhs.base();
	}

	// lhs is considered less than rhs if lhs's base iterator is less than rhs's base iterator.
	template<typename Iterator1, typename UnaryOperation1, typename Iterator2, typename UnaryOperation2>
	bool operator<(transforming_iterator<Iterator1, UnaryOperation1> const& lhs, transforming_iterator<Iterator2, UnaryOperation2> const& rhs)
	{
		return lhs.base() < rhs.base();
	}

	// lhs is considered less than or equal to rhs is lhs's base iterator is less than or equal to rhs's base iterator.
	template<typename Iterator1, typename UnaryOperation1, typename Iterator2, typename UnaryOperation2>
	bool operator<=(transforming_iterator<Iterator1, UnaryOperation1> const& lhs, transforming_iterator<Iterator2, UnaryOperation2> const& rhs)
	{
		return lhs.base() <= rhs.base();
	}

	// lhs is considered greater than rhs if lhs's base iterator is greater than rhs's base iterator.
	template<typename Iterator1, typename UnaryOperation1, typename Iterator2, typename UnaryOperation2>
	bool operator>(transforming_iterator<Iterator1, UnaryOperation1> const& lhs, transforming_iterator<Iterator2, UnaryOperation2> const& rhs)
	{
		return lhs.base() > rhs.base();
	}

	// lhs is considered greater than or equal to rhs if lhs's base iterator is greater than or equal to rhs's base iterator.
	template<typename Iterator1, typename UnaryOperation1, typename Iterator2, typename UnaryOperation2>
	bool operator>=(transforming_iterator<Iterator1, UnaryOperation1> const& lhs, transforming_iterator<Iterator2, UnaryOperation2> const& rhs)
	{
		return lhs.base() >= rhs.base();
	}

}


// Specialization for tl::iterators::transforming_iterator.
template<typename Iterator, typename UnaryOperation>
struct std::iterator_traits<tl::iterators::transforming_iterator<Iterator, UnaryOperation>> {
	using value_type = typename tl::iterators::transforming_iterator<Iterator, UnaryOperation>::value_type;
	using reference = typename tl::iterators::transforming_iterator<Iterator, UnaryOperation>::reference;
	using pointer = void;
	using difference_type = typename tl::iterators::transforming_iterator<Iterator, UnaryOperation>::difference_type;
	using iterator_category = typename tl::iterators::transforming_iterator<Iterator, UnaryOperation>::iterator_category;
};


#endif
