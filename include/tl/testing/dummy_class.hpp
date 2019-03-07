#ifndef TL_TESTING_DUMMY_CLASS_HPP
#define TL_TESTING_DUMMY_CLASS_HPP


#include <iostream>		// std::cout, std::endl


namespace tl::testing {

	// Prints to std::cout on calling of member functions such as constructors and assignments.
	struct dummy_class {
		/* Special members */

		~dummy_class()
		{
			std::cout << "Destructor" << std::endl;
		}

		dummy_class()
		{
			std::cout << "Default constructor" << std::endl;
		}

		dummy_class(dummy_class const&)
		{
			std::cout << "Copy constructor" << std::endl;
		}

		dummy_class(dummy_class&&)
		{
			std::cout << "Move constructor" << std::endl;
		}


		/* Operators */

		dummy_class& operator=(dummy_class const&)
		{
			std::cout << "Copy assignment" << std::endl;
			return *this;
		}

		dummy_class& operator=(dummy_class&&)
		{
			std::cout << "Move assignment" << std::endl;
			return *this;
		}
	};

}


#endif
