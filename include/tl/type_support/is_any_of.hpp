#ifndef TL_TYPE_SUPPORT_IS_ANY_OF_HPP
#define TL_TYPE_SUPPORT_IS_ANY_OF_HPP


#include <type_traits>		// std::disjunction, std::is_same


namespace tl::type_support {
	
	// std::true_type if T is U or any of Us, otherwise std::false_type.
	template<typename T, typename U, typename... Us>
	struct is_any_of : std::disjunction<std::is_same<T, U>, std::is_same<T, Us>...> {};

	
	template<typename T, typename U, typename... Us>
	inline constexpr bool is_any_of_v = is_any_of<T, U, Us...>::value;
	
}


#endif
