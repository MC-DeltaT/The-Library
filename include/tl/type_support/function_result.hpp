#ifndef TL_TYPE_SUPPORT_FUNCTION_RESULT_HPP
#define TL_TYPE_SUPPORT_FUNCTION_RESULT_HPP


namespace tl::type_support {

	template<typename...>
	struct function_result {};


	// Provides the type member type which is equivalent to the return type of the given function type.
	template<typename R, typename... Ts>
	struct function_result<R(Ts...)> {
		using type = R;
	};


	// Provides the type member type which is equivalent to the return type of the given function reference type.
	template<typename R, typename... Ts>
	struct function_result<R(&)(Ts...)> {
		using type = R;
	};


	// Provides the type member type which is equivalent to the return type of the given function pointer type.
	template<typename R, typename... Ts>
	struct function_result<R(*)(Ts...)> {
		using type = R;
	};


	template<typename T>
	using function_result_t = typename function_result<T>::type;

}


#endif
