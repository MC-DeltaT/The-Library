#ifndef TL_MISC_STATIC_OPTIONAL_HPP
#define TL_MISC_STATIC_OPTIONAL_HPP


namespace tl::misc {

	// Has member variable value if B is true, otherwise has no member.
	template<bool B, typename T>
	struct static_optional {};

	template<typename T>
	struct static_optional<true, T> {
		T value;
	};

}


#endif
