#ifndef TL_MEMORY_DESTROY_DESTRUCT_HPP
#define TL_MEMORY_DESTROY_DESTRUCT_HPP


#include <memory>						// std::allocator_traits
#include <tl/memory/destroy_n.hpp>		// tl::memory::destroy_n


namespace tl::memory {

	/* Destructs and deallocates one object at ptr using the given allocator.
		Calls alloc.deallocate(ptr, 1). The corresponding call to allocate() should have allocated exactly 1 object. */
	template<class Allocator>
	void destroy_destruct(Allocator& alloc, typename std::allocator_traits<Allocator>::pointer ptr)
	{
		std::allocator_traits<Allocator>::destroy(alloc, ptr);
		std::allocator_traits<Allocator>::deallocate(alloc, ptr, 1);
	}


	/* Destructs and deallocates an array of count objects at ptr using the given allocator.
		Calls alloc.deallocate(ptr, count). The corresponding call to allocate() should have allocated exactly count objects. */
	template<class Allocator>
	void destroy_destruct(Allocator& alloc, typename std::allocator_traits<Allocator>::pointer ptr, typename std::allocator_traits<Allocator>::size_type count)
	{
		destroy_n(alloc, ptr, count);
		std::allocator_traits<Allocator>::deallocate(alloc, ptr, count);
	}

}


#endif
