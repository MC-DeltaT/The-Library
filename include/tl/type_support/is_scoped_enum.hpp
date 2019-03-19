#ifndef TL_TYPE_SUPPORT_IS_SCOPED_ENUM_HPP
#define TL_TYPE_SUPPORT_IS_SCOPED_ENUM_HPP


#include <type_traits>		// std::conjunction, std::is_convertible, std::is_enum, std::negation


namespace tl::type_support {

	// std::true_type if T is a scoped enumeration type, otherwise std::false_type.
	template<typename T>
	struct is_scoped_enum : std::conjunction<std::is_enum<T>, std::negation<std::is_convertible<T, int>>> {};


	template<typename T>
	inline constexpr bool is_scoped_enum_v = is_scoped_enum<T>::value;

}


#endif
