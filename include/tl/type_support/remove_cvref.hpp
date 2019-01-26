#ifndef TL_TYPE_SUPPORT_REMOVE_CVREF_HPP
#define TL_TYPE_SUPPORT_REMOVE_CVREF_HPP


#include <type_traits>      // std::remove_cv_t, std::remove_ref_t


namespace tl::type_support {

	// Provides type member type equivalent to removing reference and then cv qualifiers, if present, from T.
    template<typename T>
    struct remove_cvref {
        using type = std::remove_cv_t<std::remove_reference_t<T>>;
    };


    template<typename T>
    using remove_cvref_t = typename remove_cvref<T>::type;

}


#endif
