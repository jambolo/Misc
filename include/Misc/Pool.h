#if !defined(MISC_POOL_H_INCLUDED)
#define MISC_POOL_H_INCLUDED
#pragma once

#include <memory>

//! A memory allocator that allocates blocks of a fixed size from a pre-allocated space.

class FixedAllocator
{
public:

    //! Constructor.
    FixedAllocator();

    //! Constructor.
    FixedAllocator(int n, void * pBuffer, size_t size);

    //! Destructor.
    ~FixedAllocator();

    //! Initializes the allocator after default constructor
    void initialize(int n, void * pBuffer, size_t size);
        
    //! Allocates a block, returning the address of the block or nullptr if error.
    void * allocate();

    //! Frees an allocated block.
    void deallocate(void * pBlock);

#if defined(_DEBUG)
    //! Returns the number of blocks that are currently allocated
    int allocations() const { return m_CurrentCount; }

    //! Returns the maximum number of concurrently allocated blocks
    int maxAllocations() const { return m_MaxCount; }
#endif // defined( _DEBUG )

private:

    // non-copyable
    FixedAllocator(FixedAllocator const &) = delete;
    FixedAllocator & operator =(FixedAllocator const &) = delete;

    void * head_ = nullptr; // A list of free blocks

#if defined(_DEBUG)
    void * buffer_;         // Start of the buffer
    int m_CurrentCount;     // Current number of blocks allocated
    int m_MaxCount;         // Maximum number of blocks allocated at one time
    size_t m_BlockSize;     // Size of a block
    size_t m_BufferSize;    // Size of the buffer
#endif // defined( _DEBUG )
};

//! A memory allocator template class that allocates the specified type from a pool of memory
//!
//! @param	Type        Type of the items contained by the pool
//! @param	Allocator   Allocator used to allocate the pool (default is std::allocator<T>)

template <typename T, class Allocator = std::allocator<T>>
class Pool
{
public:

    //! Constructor.
    //!
    //! @param  n   Maximum number of items that can be allocated from the pool
    Pool(int n)
        : buffer_(allocator_.allocate(n))
    {
        fixedAllocator_.initialize(n, buffer_, sizeof(T));
    }

    //! Destructor.
    virtual ~Pool()
    {
        allocator_.deallocate(buffer_);
    }

    //! Allocates a item from the pool. Returns 0 if the allocation fails.
    T * allocate()
    {
        return static_cast<T *>(fixedAllocator_.allocate());
    }

    //! Returns a item to the pool.
    //!
    //! @param  pItem   Item to return to the pool
    void deallocate(T * pItem)
    {
        fixedAllocator_.deallocate(pItem);
    }

#if defined(_DEBUG)
    //! Returns the number of items that are currently allocated
    int allocations()
    {
        return fixedAllocator_.allocations();
    }

    //! Returns the maximum number of concurrently allocated items
    int maxAllocations()
    {
        return fixedAllocator_.maxAllocations();
    }
#endif // defined( _DEBUG )

private:

    // non-copyable
    Pool(Pool const &) = delete;
    Pool & operator =(Pool const &) = delete;

    Allocator allocator_;           // Allocator that allocates the pool
    T * buffer_;                     // Pointer to the allocation pool
    FixedAllocator fixedAllocator_; // Allocator that allocates items from the pool
};

#endif // !defined(MISC_POOL_H_INCLUDED)
