#ifndef TL_MISC_CRTP_DERIVED_CAST_HPP
#define TL_MISC_CRTP_DERIVED_CAST_HPP


namespace tl::misc {

	// Casts a CRTP base object to its derived type.
	template<template<class> class Base, class Derived>
	Derived& crtp_derived_cast(Base<Derived>& base)
	{
		return static_cast<Derived&>(base);
	}


	// Casts a CRTP base object to its derived type.
	template<template<class> class Base, class Derived>
	Derived const& crtp_derived_cast(Base<Derived> const& base)
	{
		return static_cast<Derived const&>(base);
	}

}


#endif