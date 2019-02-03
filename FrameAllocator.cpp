#include "FrameAllocator.h"

#include "Assertx.h"

#include <cstring>

//! @param	pBuffer		Buffer from which allocations are made
//! @param	size		Size of the buffer in bytes (must be at least @p ALIGNMENT bytes)
//!
//! @note	In the Debug configuration, the bytes in the buffer are set to 0xDD
FrameAllocator::FrameAllocator(void * pBuffer, size_t size)
    : state_(new State { static_cast<char *>(pBuffer), size, nullptr })
{
    assert(pBuffer != nullptr);
    assert(size >= ALIGNMENT);

    // Start at the top of the buffer and align it
    char * point = static_cast<char *>(pBuffer) + size;
    point         = reinterpret_cast<char *>((reinterpret_cast<uintptr_t>(point)) & ~(ALIGNMENT - 1));
    state_->point = point;

#if defined(_DEBUG)
    // Mark the entire buffer as unallocated
    memset(pBuffer, 0xDD, size);
#endif // defined( _DEBUG )
}

//!
//! @note	In the Debug configuration, the bytes in the buffer are set to 0xDD before destruction
FrameAllocator::~FrameAllocator()
{
#if defined(_DEBUG)
    // Mark the entire buffer as unallocated
    memset(state_->buffer, 0xDD, state_->size);
#endif // defined( _DEBUG )
}

//! std::bad_alloc is thrown if the allocation failed.
//!
//! @param	size	Number of bytes to allocate
//!
//! @return		Address of allocated memory
//!
//! @note	In the Debug configuration, the allocated bytes are initialized to 0xCD
void * FrameAllocator::allocate(size_t size)
{
    // Force an allocation even if the size is 0. This ensures that two different allocations do return the same value.
    if (size == 0)
        size = 1;

    // Pad the size to the alignment value
    size += ALIGNMENT - 1;
    size &= ~(ALIGNMENT - 1);

    // If there is no room for the allocation, throw std::bad_alloc and return nullptr
    if (state_->point - size < state_->buffer)
        throw std::bad_alloc();

    // Allocate the space
    state_->point -= size;

#if defined(_DEBUG)
    // Mark the allocation as uninitialized
    memset(state_->point, 0xCD, size);
#endif // defined( _DEBUG )

    return static_cast<void *>(state_->point);
}

//!
//! @note	In the Debug configuration, the released bytes are set to 0xDD
void FrameAllocator::release(Frame frame)
{
    char * pFrame = static_cast<char *>(frame);

    // Make sure we aren't releasing a frame that has already been released
    assert(state_->point <= pFrame);

    // Make sure the frame value isn't outside the buffer
    assert(pFrame <= state_->buffer);

    // Make sure the frame value is still aligned
    assert_aligned(reinterpret_cast<uintptr_t>(pFrame), ALIGNMENT);

#if defined(_DEBUG)

    // Mark the data in the released frame as unallocated
    if (pFrame > state_->point)
        memset(state_->point, 0xDD, pFrame - state_->point);
#endif // defined( _DEBUG )

    // Reset the allocation point back to the start of the frame
    state_->point = pFrame;
}

struct foo
{
    int x;
};

void test()
{
    {
        FrameAllocator allocator(malloc(100), 100);

        FrameAllocator::Frame mark0 = allocator.mark();
        foo * p = (foo *)allocator.allocate(1);
        FrameAllocator::Frame mark1 = allocator.mark();
//        allocator.deallocate(p, 1);
        allocator.release(mark0);
    }
    {
        TypedFrameAllocator<int> allocator(malloc(100 * sizeof(int)), 100 * sizeof(int));

        FrameAllocator::Frame mark0 = allocator.mark();
        int * p = allocator.allocate(1);
        FrameAllocator::Frame mark1 = allocator.mark();
        allocator.deallocate(p, 1);
        allocator.release(mark0);
    }
    {
        TypedFrameAllocator<foo> allocator(malloc(100 * sizeof(foo)), 100 * sizeof(foo));

        FrameAllocator::Frame mark0 = allocator.mark();
        foo * p = allocator.allocate(1);
        FrameAllocator::Frame mark1 = allocator.mark();
        allocator.deallocate(p, 1);
        allocator.release(mark0);
    }
}
