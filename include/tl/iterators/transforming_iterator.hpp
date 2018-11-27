#ifndef TL_ITERATORS_TRANSFORMING_ITERATOR
#define TL_ITERATORS_TRANSFORMING_ITERATOR


#include <iterator>								// std::advance, std::iterator_traits
#include <tc/type_support/remove_cvref.hpp>		// tc::type_support::remove_cvref_t
#include <type_traits>							// std::invoke_result_t


namespace tl::iterators {

	// Iterator adaptor that transforms iterated values with a function.
	template<typename Iterator, typename UnaryFunction>
	class transforming_iterator {
	public:
		/* Member types */

		using iterator_type = Iterator;
		using reference = std::invoke_result_t<UnaryFunction, typename std::iterator_traits<Iterator>::reference>;
		using value_type = type_support::remove_cvref_t<reference>;
		using difference_type = typename std::iterator_traits<Iterator>::difference_type;
		using iterator_category = typename std::iterator_traits<Iterator>::iterator_category;


		/* Special members */

		/* Destructor.
			Defaulted. */
		~transforming_iterator() = default;

		/* Default constructor.
			Value-initializes base iterator and function object. */
		transforming_iterator() :
			_func(),
			_it()
		{}

		/* Copy constructor.
			Defaulted. */
		transforming_iterator(transforming_iterator const&) = default;

		/* Move constructor.
			Defaulted. */
		transforming_iterator(transforming_iterator&&) = default;

		// Constructor from base iterator and function.
		transforming_iterator(Iterator base, UnaryFunction func) :
			_func(func),
			_it(base)
		{}


		/* Operators */

		/* Simple assignment - copy.
			Defaulted. */
		transforming_iterator& operator=(transforming_iterator const&) = default;

		/* Simple assignment - move.
			Defaulted. */
		transforming_iterator& operator=(transforming_iterator&&) = default;

		/* Addition assignment - advance.
			Advances base iterator by n. */
		transforming_iterator& operator+=(difference_type n)
		{
			std::advance(_it, n);

			return *this;
		}

		/* Subtraction assignment - backwards advance.
			Advances base iterator by -n. */
		transforming_iterator& operator-=(difference_type n)
		{
			std::advance(_it, -n);

			return *this;
		}

		/* Indirection - iterator dereference.
			Dereferences base iterator, applies the function, then returns the result. */
		reference operator*() const
		{
			return _func(*_it);
		}

		/* Subscript - offset dereference.
			Offset dereferences base iterator, applies the function, then returns the result. */
		reference operator[](difference_type n) const
		{
			return _func(_it[n]);
		}

		/* Pre-increment - single advance.
			Pre-increments base iterator. Returns new state. */
		transforming_iterator& operator++()
		{
			++_it;

			return *this;
		}

		/* Post-increment - single advance.
			Post-increments base iterator. Returns previous state. */
		transforming_iterator operator++(int)
		{
			auto tmp = *this;

			operator++();

			return tmp;
		}

		/* Pre-decrement - single backwards advance.
			Pre-decrements base iterator. Returns new state. */
		transforming_iterator& operator--()
		{
			--_it;

			return *this;
		}

		/* Post-decrement - single backwards advance.
			Post-decrements base iterator. Returns previous state. */
		transforming_iterator operator--(int)
		{
			auto tmp = *this;

			operator--();

			return tmp;
		}


		/* General functions */

		// Gets the base iterator.
		Iterator base() const
		{
			return _it;
		}

		// Gets the transformer function.
		UnaryFunction function() const
		{
			return _func;
		}


	private:
		/* Variables */

		UnaryFunction _func;
		Iterator _it;
	};

}


/* Specialisation for tl::iterators::transforming_iterator.
 	Does not provide the pointer type, because it makes no sense for that iterator type, and is never used anyway. */
template<typename Iterator, typename UnaryFunction>
struct std::iterator_traits<tl::iterators::transforming_iterator<Iterator, UnaryFunction>> {
	using value_type = typename tl::iterators::transforming_iterator<Iterator, UnaryFunction>::value_type;
	using reference = typename tl::iterators::transforming_iterator<Iterator, UnaryFunction>::reference;
	using difference_type = typename tl::iterators::transforming_iterator<Iterator, UnaryFunction>::difference_type;
	using iterator_category = typename tl::iterators::transforming_iterator<Iterator, UnaryFunction>::iterator_category;
};


#endif
