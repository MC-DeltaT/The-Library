#ifndef TL_MEMORY_DESTROY_N_HPP
#define TL_MEMORY_DESTROY_N_HPP


#include <memory>		// std::allocator_traits


namespace tl::memory {

	// Destructs count objects starting at ptr using the given allcoator.
	template<class Allocator>
	void destroy_n(Allocator& alloc, typename std::allocator_traits<Allocator>::pointer ptr, typename std::allocator_traits<Allocator>::size_type count)
	{
		for (decltype(count) i{}; i < count; ++i) {
			std::allocator_traits<Allocator>::destroy(alloc, ptr + i);
		}
	}

}


#endif
