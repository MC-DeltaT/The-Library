#ifndef TL_MEMORY_ALLOCATE_CONSTRUCT_HPP
#define TL_MEMORY_ALLOCATE_CONSTRUCT_HPP


#include <memory>		// std::allocator_traits
#include <utility>		// std::forward


namespace tl::memory {

	/* Allocates memory for and constructs one object using the given allocator and constructor arguments. Returns a pointer to the object.
		Calls alloc.allocate() with an argument of exactly 1. 1 should be passed to the corresponding call to alloc.deallocate(). */
	template<class Allocator, typename... Args>
	typename std::allocator_traits<Allocator>::pointer allocate_construct(Allocator& alloc, Args&&... args)
	{
		typename std::allocator_traits<Allocator>::pointer ptr = std::allocator_traits<Allocator>::allocate(alloc, 1);
		std::allocator_traits<Allocator>::construct(alloc, ptr, std::forward<Args>(args)...);
		return ptr;
	}

}


#endif
