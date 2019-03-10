#ifndef TL_CONTAINERS_SHARED_ARRAY_HPP
#define TL_CONTAINERS_SHARED_ARRAY_HPP


#include <atomic>			// std::atomic_size_t
#include <cstddef>			// std::size_t
#include <memory>			// std::allocator, std::allocator_traits
#include <type_traits>		// std::conditional_t
#include <utility>			// std::swap

#include <tl/memory/allocate_default_construct.hpp>		// tl::memory::allocate_default_construct
#include <tl/memory/destroy_deallocate.hpp>				// tl::memory::destroy_deallocate
#include <tl/utility/assign_default.hpp>				// tl::utility::assign_default


namespace tl::containers {

	namespace detail {

		// Stores the shared state for shared_array.
		template<typename Pointer, typename SizeType, bool AtomicRefCount>
		struct shared_array_state {
			// Pointer to the actual array data.
			Pointer data;

			// Number of shared_array objects currently sharing the array.
			std::conditional_t<AtomicRefCount, std::atomic_size_t, std::size_t> refs;

			// Number of elements in the array pointed to by data.
			SizeType size;
		};

	}


	/* Manages an array whose ownership can be shared by multiple shared_array objects.
		Once all shared_array objects sharing an array are destroyed, the array is also destroyed.
		If AtomicRefCount is true then a single array can be safely shared across multiple threads, but may introduce a slight performance overhead
		(however, individual array elements remain unsychronised and the user must ensure appropriate thread safety). */
	template<typename T, bool AtomicRefCount = true, class Allocator = std::allocator<T>>
	class shared_array {
	public:
		/* Member types */

		using value_type = T;
		using allocator_type = Allocator;
		using size_type = typename std::allocator_traits<Allocator>::size_type;
		using reference = T&;
		using const_reference = T const&;
		using pointer = typename std::allocator_traits<Allocator>::pointer;
		using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
		using iterator = pointer;
		using const_iterator = const_pointer;


		/* Special members */

		// If this is the last shared_array object sharing the array, the array is destroyed. Destructs allocator.
		~shared_array()
		{
			if (_state && --_state->refs == 0) {
				// Destroy the array.
				memory::destroy_deallocate(_alloc, _state->data, _state->size);

				// Destroy the shared state object.
				_state_alloc_t state_alloc(_alloc);
				memory::destroy_deallocate(state_alloc, _state, 1);
			}
		}

		// Constructs to have no array and default constructs the allocator.
		shared_array() :
			_alloc(),
			_state()
		{}

		// Constructs to share ownership of other's array, and copy-constructs allocator from other.
		shared_array(shared_array const& other) :
			_alloc(other._alloc),
			_state(other._state)
		{
			if (_state) {
				++_state->refs;
			}
		}

		// Transfers other's array ownership to this, and move-constructs allocator from other.
		shared_array(shared_array&& other) :
			shared_array()
		{
			swap(*this, other);
		}

		// Constructs the allocator from the given value then constructs an array of the given size with default-constructed elements.
		shared_array(size_type size, Allocator alloc = Allocator()) :
			_alloc(alloc),
			_state(memory::allocate_default_construct(_state_alloc_t(_alloc)))
		{
			_state->data = memory::allocate_default_construct(_alloc, size);
			_state->refs = 1;
			_state->size = size;
		}


		/* Operators */

		// Releases ownership of current array, shares ownership of rhs's array, and copy/move-assigns allocator from rhs.
		shared_array& operator=(shared_array rhs)
		{
			swap(*this, rhs);

			return *this;
		}

		// Gets a reference to the element at the given index.
		reference operator[](size_type i)
		{
			return _state->data[i];
		}

		// Gets a const reference to the element at the given index.
		const_reference operator[](size_type i) const
		{
			return _state->data[i];
		}


		/* General functions */

		// Gets an iterator to the start of the array.
		iterator begin()
		{
			return _state->data;
		}

		// Gets a const iterator to the start of the array.
		iterator begin() const
		{
			return _state->data;
		}

		// Gets a const iterator to the start of the array.
		iterator cbegin() const
		{
			return _state->data;
		}

		// Gets an const iterator to the end of the array.
		iterator cend() const
		{
			return _state->data + _state->size;
		}

		// Gets a pointer to the start of the array.
		pointer data()
		{
			return _state->data;
		}

		// Gets a const pointer to the start of the array.
		const_pointer data() const
		{
			return _state->data;
		}

		// Gets an iterator to the end of the array.
		iterator end()
		{
			return _state->data + _state->size;
		}

		// Gets an const iterator to the end of the array.
		iterator end() const
		{
			return _state->data + _state->size;
		}

		// Gets the number of elements in the array.
		size_type size() const
		{
			return _state->size;
		}


		/* Friend functions */

		// Swaps the contents of first and second.
		friend void swap(shared_array& first, shared_array& second)
		{
			using std::swap;

			swap(first._alloc, second._alloc);
			swap(first._state, second._state);
		}


	private:
		/* Member types */

		using _state_t = detail::shared_array_state<pointer, size_type, AtomicRefCount>;

		// Allocator type to be used for allocation of the shared state object.
		using _state_alloc_t = typename std::allocator_traits<Allocator>::template rebind_alloc<_state_t>;

		using _state_pointer = typename std::allocator_traits<_state_alloc_t>::pointer;


		/* Variables */

		/* Allocator to use for all memory allocations.
			Mutable because const-qualified allocators aren't required to be useful. */
		mutable Allocator _alloc;

		// Pointer to the shared array state.
		_state_pointer _state;
	};

}


#endif
