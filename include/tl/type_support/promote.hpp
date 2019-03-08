#ifndef TL_TYPE_SUPPORT_PROMOTE_HPP
#define TL_TYPE_SUPPORT_PROMOTE_HPP


#include <type_traits>			// std::enable_if_t, std::is_integral_v
#include <utility>				// std::declval

#include <tl/type_support/is_unscoped_enum.hpp>		// tl::type_support::is_unscoped_enum_v


namespace tl::type_support {

	namespace detail {

		// Matches non-promotable types.
		template<typename T, typename = void>
		struct promote_base {
			using type = T;
		};

		// Matches promotable types.
		template<typename T>
		struct promote_base<T, std::enable_if_t<std::is_integral_v<T> || is_unscoped_enum_v<T>, void>> {
			using type = decltype(+std::declval<T>());
		};

	}

	// Provides type member type which is the integer promoted T if T may undergo integer promotion, otherwise is T.
	template<typename T>
	struct promote : detail::promote_base<T> {};


	template<typename T>
	using promote_t = typename promote<T>::type;

}


#endif
