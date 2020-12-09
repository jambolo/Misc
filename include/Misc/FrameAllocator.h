#if !defined(MISC_FRAMEALLOCATOR_H_INCLUDED)
#define MISC_FRAMEALLOCATOR_H_INCLUDED
#pragma once

#include <memory>

//! A frame-based allocator.

class FrameAllocator
{
public:

    using Frame = void *;  //!< A frame boundary

    //! Constructor.
    FrameAllocator(void * pBuffer, size_t size);

    //! Destructor.
    ~FrameAllocator();

    //! Allocates uninitialized storage.
    void * allocate(size_t size);

    //! Returns the largest value that can be passed to allocate().
    size_t max_size() const { return state_->point - state_->buffer;  }

    //! Marks the start of a frame.
    Frame mark() const { return static_cast<Frame>(state_->point); }

    //! Deallocates all memory allocated in the specified frame.
    void release(Frame frame);

    //! Returns true if the allocators are the same
    bool operator ==(FrameAllocator const & a2) const { return this->state_ == a2.state_; }

private:

    static size_t constexpr ALIGNMENT = 8;          // Allocation and size alignment

    struct State
    {
        char * buffer;  // Start of the allocation buffer
        size_t size;    // Size of the buffer
        char * point;   // Current allocation point
    };

    // The state is shared so that the allocator copies satisfy the requirement "a1 == a2"
    std::shared_ptr<State> state_;
};

//! A frame-based allocator compatible with std containers.

template <typename T>
class TypedFrameAllocator
{
public:

    using Frame = void *;  //!< A frame boundary

    //! Constructor.
    //!
    //! @param	pBuffer		Buffer from which allocations are made
    //! @param	size		Size of the buffer in bytes (must be at least @p ALIGNMENT bytes)
    //!
    //! @note	In the Debug configuration, the bytes in the buffer are set to 0xDD
    TypedFrameAllocator(void * pBuffer, size_t size)
        : allocator_(pBuffer, size)
    {
    }

    //! Destructor.
    //!
    //! @note	In the Debug configuration, the bytes in the buffer are set to 0xDD before destruction
    ~TypedFrameAllocator() = default;

    //! Allocates uninitialized storage.
    //!
    //! std::bad_alloc is thrown if the allocation failed.
    //!
    //! @param	size	Number of bytes to allocate
    //!
    //! @return		Allocated memory, or nullptr0 if the space could not be allocated
    //!
    //! @note	In the Debug configuration, the allocated bytes are initialized to 0xCD
    T * allocate(size_t size)
    {
        return static_cast<T *>(allocator_.allocate(size * sizeof(T)));
    }

    //! Does nothing (included for compatibility with C++ Allocator named requirement).
    void deallocate(T *, size_t)
    {
    }

    //! Returns the largest value that can be passed to allocate().
    size_t max_size() const
    {
        return allocator_.max_size() / sizeof(T);
    }

    // For std::allocator_traits
    using propagate_on_container_copy_assignment = std::true_type;  //!< For std::allocator_traits
    using propagate_on_container_move_assignment = std::false_type; //!< For std::allocator_traits
    using propagate_on_container_swap = std::true_type;             //!< For std::allocator_traits
    using is_always_equal = std::false_type;                        //!< For std::allocator_traits

    //! Marks the start of a frame.
    //!
    //! @return     The mark for use with release()
    Frame mark() const
    {
        return allocator_.mark();
    }

    //! Deallocates all memory allocated in the specified frame.
    //!
    //! @note	In the Debug configuration, the released bytes are set to 0xDD
    void release(Frame frame)
    {
        allocator_.release(frame);
    }

    //! Returns true if the allocators are the same
    bool operator ==(TypedFrameAllocator const & a2) const
    {
        return allocator_ == a2.allocator_;
    }

private:

    FrameAllocator allocator_;
};

template <typename T>
bool operator ==(TypedFrameAllocator<T> const & a1, TypedFrameAllocator<T> const & a2)
{
    return a1.operator ==(a2);
}

template <typename T>
bool operator !=(TypedFrameAllocator<T> const & a1, TypedFrameAllocator<T> const & a2)
{
    return !a1.operator ==(a2);
}

#endif // !defined(MISC_FRAMEALLOCATOR_H_INCLUDED)
