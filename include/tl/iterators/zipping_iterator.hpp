#ifndef TL_ITERATORS_ZIPPING_ITERATOR_HPP
#define TL_ITERATORS_ZIPPING_ITERATOR_HPP


#include <cstdlib>					// std::abs
#include <functional>				// std::equal_to, std::logical_or, std::minus
#include <iterator>					// std::iterator_traits
#include <tl/tuple/foldl.hpp>		// tl::tuple::foldl
#include <tl/tuple/for_each.hpp>	// tl::tuple::for_each
#include <tl/tuple/transform.hpp>	// tl::tuple::transform
#include <tuple>					// std::tuple
#include <type_traits>				// std::common_type_t


namespace tl::iterators {

	// Iterator adaptor that iterates multiple iterators simultaneouly and dereferences to a tuple of the results of dereferencing each iterator.
	template<typename... Iterators>
	class zipping_iterator {
	public:
		/* Member types */

		using value_type = std::tuple<typename std::iterator_traits<Iterators>::value_type...>;
		using reference = std::tuple<typename std::iterator_traits<Iterators>::reference...>;
		using difference_type = std::common_type_t<typename std::iterator_traits<Iterators>::difference_type...>;
		using iterator_category = std::common_type_t<typename std::iterator_traits<Iterators>::iterator_category...>;


		/* Special members */

		// Destructs the base iterators.
		~zipping_iterator() = default;

		// Value-initializes the base iterators.
		zipping_iterator() :
			_iterators()
		{}

		// Copy-constructs the base iterators from those of other.
		zipping_iterator(zipping_iterator const& other) = default;

		// Move-constructs the base iterators from those of other.
		zipping_iterator(zipping_iterator&& other) = default;

		// Constructs the base iterators from a parameter pack of iterators.
		explicit zipping_iterator(Iterators... iterators) :
			_iterators(iterators...)
		{}

		// Constructs the base iterators from a tuple of iterators.
		explicit zipping_iterator(std::tuple<Iterators...> iterators) :
			_iterators(iterators)
		{}


		/* Operators */

		// Copy-assigns the base iterators from those of rhs.
		zipping_iterator& operator=(zipping_iterator const& rhs) = default;

		// Move-assigns the base iterators from those of rhs.
		zipping_iterator& operator=(zipping_iterator&& rhs) = default;

		// Advances the base iterators by n.
		zipping_iterator& operator+=(difference_type n)
		{
			tuple::for_each(_iterators, [n](auto& it) {
					it += n;
				});

			return *this;
		}

		// Advances the base iterators by -n.
		zipping_iterator& operator-=(difference_type n)
		{
			tuple::for_each(_iterators, [n](auto& it) {
					it -= n;
				});

			return *this;
		}

		// Returns a tuple containing the results of dereferencing each base iterator.
		reference operator*() const
		{
			return tuple::transform(_iterators, [](auto const& it) -> decltype(auto) {
					return *it;
				});
		}

		// Returns a tuple containing the results of dereferencing each base iterator at an offset of n.
		reference operator[](difference_type n) const
		{
			return tuple::transform(_iterators, [n](auto const& it) -> decltype(auto) {
					return it[n];
				});
		}

		// Increments the base iterators, then returns the new state.
		zipping_iterator& operator++()
		{
			tuple::for_each(_iterators, [](auto& it) {
					++it;
				});

			return *this;
		}

		// Increments the base iterators, then returns the previous state.
		zipping_iterator operator++(int)
		{
			auto tmp = *this;

			operator++();

			return tmp;
		}

		// Decrements the base iterators, then returns the new state.
		zipping_iterator& operator--()
		{
			tuple::for_each(_iterators, [](auto& it) {
					--it;
				});

			return *this;
		}

		// Decrements the base iterators, then returns the previous state.
		zipping_iterator operator--(int)
		{
			auto tmp = *this;

			operator--();

			return tmp;
		}


		/* General functions */

		// Gets a tuple of the base iterators.
		std::tuple<Iterators...> const& base() const
		{
			return _iterators;
		}


	private:
		/* Variables */

		std::tuple<Iterators...> _iterators;
	};


	// Returns a copy of lhs advanced by rhs. */
	template<typename... Iterators>
	zipping_iterator<Iterators...> operator+(zipping_iterator<Iterators...> const& lhs, typename zipping_iterator<Iterators...>::difference_type rhs)
	{
		auto tmp = lhs;
		tmp += rhs;

		return tmp;
	}

	// Returns a copy of rhs advanced by lhs. */
	template<typename... Iterators>
	zipping_iterator<Iterators...> operator+(typename zipping_iterator<Iterators...>::difference_type lhs, zipping_iterator<Iterators...> const& rhs)
	{
		auto tmp = rhs;
		tmp += lhs;

		return tmp;
	}

	// Returns a copy of lhs advanced by -rhs. */
	template<typename... Iterators>
	zipping_iterator<Iterators...> operator-(zipping_iterator<Iterators...> const& lhs, typename zipping_iterator<Iterators...>::difference_type rhs)
	{
		auto tmp = lhs;
		tmp -= rhs;

		return tmp;
	}

	/* Returns the smallest (in magnitude) of the differences between the corresponding pairs of iterators from lhs and rhs.
		If multiple pairs have the same magnitude of difference, the first is chosen. */
	template<typename... Iterators1, typename... Iterators2>
	auto operator-(zipping_iterator<Iterators1...> const& lhs, zipping_iterator<Iterators2...> const& rhs)
	{
		auto diff = tuple::transform(lhs.base(), rhs.base(), std::minus());
		return tuple::foldl(diff, [](auto a, auto b) {
				if (std::abs(b) < std::abs(a)) {
					return b;
				}
				else {
					return a;
				}
			});
	}

	// lhs and rhs are considered equal if any of their corresponding pairs of base iterators are equal.
	template<typename... Iterators1, typename... Iterators2>
	bool operator==(zipping_iterator<Iterators1...> const& lhs, zipping_iterator<Iterators2...> const& rhs)
	{
		return tuple::foldl(tuple::transform(lhs.base(), rhs.base(), std::equal_to()), std::logical_or());
	}

	// lhs and rhs are considered unequal if none of their corresponding pairs of base iterators are equal.
	template<typename... Iterators1, typename... Iterators2>
	bool operator!=(zipping_iterator<Iterators1...> const& lhs, zipping_iterator<Iterators2...> const& rhs)
	{
		return !(lhs == rhs);
	}

	// lhs is considered less than rhs if (lhs - rhs) < 0.
	template<typename... Iterators1, typename... Iterators2>
	bool operator<(zipping_iterator<Iterators1...> const& lhs, zipping_iterator<Iterators2...> const& rhs)
	{
		return lhs - rhs < 0;
	}

	// lhs is considered less than or equal to rhs if (lhs - rhs) <= 0.
	template<typename... Iterators1, typename... Iterators2>
	bool operator<=(zipping_iterator<Iterators1...> const& lhs, zipping_iterator<Iterators2...> const& rhs)
	{
		return !(lhs > rhs);
	}

	// lhs is considered greater than rhs if (lhs - rhs) > 0.
	template<typename... Iterators1, typename... Iterators2>
	bool operator>(zipping_iterator<Iterators1...> const& lhs, zipping_iterator<Iterators2...> const& rhs)
	{
		return rhs < lhs;
	}

	// lhs is considered greater than or equal to rhs if (lhs - rhs) >= 0.
	template<typename... Iterators1, typename... Iterators2>
	bool operator>=(zipping_iterator<Iterators1...> const& lhs, zipping_iterator<Iterators2...> const& rhs)
	{
		return !(lhs < rhs);
	}

}


// Specialization for tl::iterators::zipping_iterator.
template<typename... Iterators>
struct std::iterator_traits<tl::iterators::zipping_iterator<Iterators...>> {
	using value_type = typename tl::iterators::zipping_iterator<Iterators...>::value_type;
	using reference = typename tl::iterators::zipping_iterator<Iterators...>::reference;
	using pointer = void;
	using difference_type = typename tl::iterators::zipping_iterator<Iterators...>::difference_type;
	using iterator_category = typename tl::iterators::zipping_iterator<Iterators...>::iterator_category;
};


#endif
