#ifndef TL_TYPE_SUPPORT_IS_UNSCOPED_ENUM_HPP
#define TL_TYPE_SUPPORT_IS_UNSCOPED_ENUM_HPP


#include <type_traits>		// std::conjunction, std::is_convertible, std::is_enum


namespace tl::type_support {

	// std::true_type if T is an unscoped enumeration type, otherwise std::false_type.
	template<typename T>
	struct is_unscoped_enum : std::conjunction<std::is_enum<T>, std::is_convertible<T, int>> {};


	template<typename T>
	inline constexpr bool is_unscoped_enum_v = is_unscoped_enum<T>::value;

}


#endif
