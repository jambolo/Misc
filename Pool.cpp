#include "Pool.h"

#include <cassert>
#include <cstring>
#include <stdexcept>

namespace
{
size_t constexpr LINK_SIZE = sizeof(void **);

bool empty(void * head)
{
    return head == nullptr;
}

void push(void *& head, void * pBlock)
{
    void ** link = static_cast<void **>(pBlock);
    *link = head;
    head  = pBlock;
}

void * pop(void *& head)
{
    if (!head)
        return nullptr;

    void * pBlock = head;
    head = *static_cast<void **>(pBlock);
    return pBlock;
}
}

FixedAllocator::FixedAllocator()
#if defined(_DEBUG)
    : buffer_(nullptr)
    , m_CurrentCount(0)
    , m_MaxCount(0)
    , m_BlockSize(sizeof(void *))
    , m_BufferSize(0)
#endif // defined( _DEBUG )
{
}

//! @param  n       Number of blocks that can be allocated from the pool
//! @param  pBuffer Space to hold the blocks (must be correctly aligned and large enough to hold @a n blocks)
//! @param  size    Size of a block in bytes. The size must be at least sizeof(void **) (8 bytes).
//!
//! @note	In the Debug configuration, the bytes in the buffer are set to 0xDD

FixedAllocator::FixedAllocator(int n, void * pBuffer, size_t size)
{
    initialize(n, pBuffer, size);
}

//! @param  n       Number of blocks that can be allocated from the pool
//! @param  pBuffer Space to hold the blocks (must be correctly aligned and large enough to hold @a n blocks)
//! @param  size    Size of a block in bytes. The size must be at least sizeof(void **) (8 bytes).
//!
//! @note	In the Debug configuration, the bytes in the buffer are set to 0xDD

void FixedAllocator::initialize(int n, void * pBuffer, size_t size)
{
#if defined(_DEBUG)
    buffer_ = pBuffer;
    m_CurrentCount = 0;
    m_MaxCount = n;
    m_BlockSize = size;
    m_BufferSize = n * size;
#endif // defined( _DEBUG )

    // Should not have already been initialized
    assert(!head_);

    // Minimum block size is the size of a void *
    assert(size >= LINK_SIZE);

#if defined(_DEBUG)
    // Fill the space with unallocated data
    if (m_BufferSize > 0)
        memset(buffer_, 0xDD, m_BufferSize);
#endif // defined( _DEBUG )

    // Add all the blocks to the free block list
    char * pBlock = static_cast<char *>(pBuffer);
    for (int i = 0; i < n; i++)
    {
        push(head_, pBlock);
        pBlock += size;
    }
}

//!
//! @note   In the Debug configuration, the bytes in the buffer are set to 0xDD

FixedAllocator::~FixedAllocator()
{
#if defined(_DEBUG)
    // Fill the space with unallocated data
    if (m_BufferSize > 0)
        memset(buffer_, 0xDD, m_BufferSize);
#endif // defined( _DEBUG )
}

//!
//! @note   n the Debug configuration, the allocated bytes are set to 0xCD

void * FixedAllocator::allocate()
{
    // If all the blocks have been allocated, then return nullptr
    if (empty(head_))
        return nullptr;

    // Get a block from the list of free blocks and remove it from the list
    void * pBlock = pop(head_);

#if defined(_DEBUG)
    ++m_CurrentCount;
    memset(pBlock, 0xCD, m_BlockSize);
#endif // defined( _DEBUG )

    return pBlock;
}

//!
//! @note   n the Debug configuration, the freed bytes are set to 0xDD

void FixedAllocator::deallocate(void * pBlock)
{
#if defined(_DEBUG)
    memset(pBlock, 0xDD, m_BlockSize);
    --m_CurrentCount;
#endif // defined( _DEBUG )

    // Add the block to the free block list
    push(head_, pBlock);
}
