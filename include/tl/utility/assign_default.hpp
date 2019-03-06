#ifndef TL_UTILITY_ASSIGN_DEFAULT_HPP
#define TL_UTILITY_ASSIGN_DEFAULT_HPP


namespace tl::utility {

	// Move-assigns a default-constructed T to object.
	template<typename T>
	void assign_default(T& object)
	{
		object = T();
	}

}


#endif
