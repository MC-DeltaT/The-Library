#ifndef TL_TYPE_SUPPORT_IS_INT_HPP
#define TL_TYPE_SUPPORT_IS_INT_HPP


#include <type_traits>			// std::remove_cv_t

#include <tl/type_support/is_any_of.hpp>		// tl::type_support::is_any_of


namespace tl::type_support {

	namespace detail {

		// std::true_type if T is int or any size/signedness modification thereof, otherwise std::false_type.
		template<typename T>
		struct is_int_base : is_any_of<T, short, int, long, long long,
			unsigned short, unsigned, unsigned long, unsigned long long> {};

	}


	/* std::true_type if T is int or any cv-qualified, size/signedness modification thereof, otherwise std::false_type.
		Eg. std::true_type for int, const int, short, volatile short, unsigned, const unsigned, etc. */
	template<typename T>
	struct is_int : detail::is_int_base<std::remove_cv_t<T>> {};


	template<typename T>
	inline constexpr bool is_int_v = is_int<T>::value;

}


#endif
