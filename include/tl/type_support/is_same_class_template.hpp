#ifndef TL_TYPE_SUPPORT_IS_SAME_CLASS_TEMPLATE_HPP
#define TL_TYPE_SUPPORT_IS_SAME_CLASS_TEMPLATE_HPP


#include <type_traits>			// std::false_type, std::true_type


namespace tl::type_support {

	namespace detail {

		// Matches different class templates.
		template<template<typename...> class T, template<typename...> class U>
		struct is_same_class_template_impl : std::false_type {};


		// Matches same class templates.
		template<template<typename...> class T>
		struct is_same_class_template_impl<T, T> : std::true_type {};

	}


	template<template<typename...> class T, template<typename...> class U>
	struct is_same_class_template : detail::is_same_class_template_impl<T, U> {};


	template<template<typename...> class T, template<typename...> class U>
	inline constexpr bool is_same_class_template_v = is_same_class_template<T, U>::value;

}


#endif
