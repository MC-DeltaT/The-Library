#ifndef TL_TYPE_SUPPORT_IS_UNSCOPED_ENUM_HPP
#define TL_TYPE_SUPPORT_IS_UNSCOPED_ENUM_HPP


#include <type_traits>		// std::integral_constant, std::is_convertible_v, std::is_enum_v


namespace tl::type_support {
	
	// std::true_type if T is an unscoped enumeration type, otherwise std::false_type.
	template<typename T>
	struct is_unscoped_enum : std::integral_constant<bool, std::is_enum_v<T> && std::is_convertible_v<T, int>> {};

		
	template<typename T>
	inline constexpr bool is_unscoped_enum_v = is_unscoped_enum<T>::value;
	
}


#endif
