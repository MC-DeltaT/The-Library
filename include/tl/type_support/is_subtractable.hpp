#ifndef TL_TYPE_SUPPORT_IS_SUBTRACTABLE_HPP
#define TL_TYPE_SUPPORT_IS_SUBTRACTABLE_HPP


#include <type_traits>		// std::false_type, std::true_type, std::void_t
#include <utility>			// std::declval


namespace tl::type_support {

	namespace detail {

		// Matches if T - U is invalid.
		template<typename T, typename U, typename = std::void_t<>>
		struct is_subtractable_base : std::false_type {};

		// Matches if T - U is valid.
		template<typename T, typename U>
		struct is_subtractable_base<T, U, std::void_t<decltype(std::declval<T>() - std::declval<U>())>> : std::true_type {};

	}


	// std::true_type if T - U is a valid expression for objects of those types, otherwise std::false_type.
	template<typename T, typename U>
	struct is_subtractable : detail::is_subtractable_base<T, U> {};


	template<typename T, typename U>
	inline constexpr bool is_subtractable_v = is_subtractable<T, U>::value;

}


#endif
