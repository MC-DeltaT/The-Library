#ifndef TL_TYPE_SUPPORT_IS_CLASS_TEMPLATE_INSTANCE_HPP
#define TL_TYPE_SUPPORT_IS_CLASS_TEMPLATE_INSTANCE_HPP


#include <type_traits>			// std::false_type, std::true_type


namespace tl::type_support {

	namespace detail {

		// Matches if T is not an instance of U.
		template<typename T, template<typename...> class U>
		struct is_class_template_instance_impl : std::false_type {};


		// Matches if T is an instance of U.
		template<typename T, template<typename...> class U>
		struct is_class_template_instance_impl<U<T>, U> : std::true_type {};

	}


	/* std::true_type if T is an instance of the class template U, otherwise std::false_type.
		Only works if the class template U has only type template parameters. */
	template<typename T, template<typename...> class U>
	struct is_class_template_instance : detail::is_class_template_instance_impl<T, U> {};


	template<typename T, template<typename...> class U>
	inline constexpr bool is_class_template_instance_v = is_class_template_instance<T, U>::value;

}


#endif
