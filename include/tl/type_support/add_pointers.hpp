#ifndef TL_TYPE_SUPPORT_ADD_POINTERS_HPP
#define TL_TYPE_SUPPORT_ADD_POINTERS_HPP


#include <cstddef>			// std::size_t
#include <type_traits>		// std::add_pointer


namespace tl::type_support {

	// Provides type member type which is equivalent to adding N levels of pointers to T.
	template<typename T, std::size_t N>
	struct add_pointers : std::add_pointer<typename add_pointers<T, N - 1>::type> {};

	// Specialization for adding zero levels of pointers; type is equivalent to T.
	template<typename T>
	struct add_pointers<T, 0> {
		using type = T;
	};


	template<typename T, std::size_t N>
	using add_pointers_t = typename add_pointers<T, N>::type;

}


#endif
