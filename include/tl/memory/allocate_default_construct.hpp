#ifndef TL_MEMORY_ALLOCATE_DEFAULT_CONSTRUCT_HPP
#define TL_MEMORY_ALLOCATE_DEFAULT_CONSTRUCT_HPP


#include <memory>		// std::allocator_traits
#include <utility>		// std::forward


namespace tl::memory {

	// Allocates memory for and default constructs one object using the given allocator. Returns a pointer to the object.
	template<class Allocator, typename... Args>
	typename std::allocator_traits<Allocator>::pointer allocate_default_construct(Allocator& alloc)
	{
		typename std::allocator_traits<Allocator>::pointer ptr = std::allocator_traits<Allocator>::allocate(alloc, 1);
		std::allocator_traits<Allocator>::construct(alloc, ptr);
		return ptr;
	}


	// Allocates memory for and default constructs an array of count objects using the given allocator. Returns a pointer to the first object.
	template<class Allocator, typename... Args>
	typename std::allocator_traits<Allocator>::pointer
		allocate_default_construct(Allocator& alloc, typename std::allocator_traits<Allocator>::size_type count)
	{
		typename std::allocator_traits<Allocator>::pointer ptr = std::allocator_traits<Allocator>::allocate(alloc, count);
		for (decltype(count) i{}; i < count; ++i) {
			std::allocator_traits<Allocator>::construct(alloc, ptr + i);
		}
		return ptr;
	}

}


#endif
