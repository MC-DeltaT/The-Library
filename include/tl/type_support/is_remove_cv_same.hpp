#ifndef TL_TYPE_SUPPORT_IS_REMOVE_CV_SAME_HPP
#define TL_TYPE_SUPPORT_IS_REMOVE_CV_SAME_HPP


#include <type_traits>			// std::is_same, std::remove_cv_t


namespace tl::type_support {

	// std::true_type if, removing topmost cv-qualifications, T and U are the same type, otherwise std::false_type.
	template<typename T, typename U>
	struct is_remove_cv_same : std::is_same<std::remove_cv_t<T>, std::remove_cv_t<U>> {};


	template<typename T, typename U>
	inline constexpr bool is_remove_cv_same_v = is_remove_cv_same<T, U>::value;

}


#endif
