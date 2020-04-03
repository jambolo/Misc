#pragma once

#include <Afx.h>

//! This macro asserts that @a v is between @a l and @a h (inclusive)
//!
//! @param	l,h		Upper and lower limits. @a l must be <= @a h.
//! @param	v		Value to check
//!
//! @hideinitializer

#if defined(_DEBUG)

#define ASSERT_LIMITS(l, v, h)                                                       \
    do                                                                               \
    {                                                                                \
        if (!((l) <= (v) && (v) <= (h)) && AfxAssertFailedLine(THIS_FILE, __LINE__)) \
        {                                                                            \
            AfxDebugBreak();                                                         \
        }                                                                            \
    } while (0)

#else // defined ( _DEBUG )

#define ASSERT_LIMITS(l, v, h)

#endif // defined(_DEBUG)

//! This macro asserts that a call to memset with the specified value and destination will work as expected.
//!
//! The problem with memset is that it sets @b byte values but does not check the destination to make sure that it
//! is an array of bytes or that the value being set fits in a byte.
//!
//! This assert checks if the value being set fits in a byte. It also makes sure that if the size of the destination
//! elements is > 1, then the value being set is 0 or -1. Only 0 and -1 will work as expected if the size of the
//! destination elements is more than 1 byte.
//!
//! @param	d	Destination address
//! @param	v	Value to be set
//!
//! @note
//! Unfortunately, this assert cannot catch all cases of the value fitting in a byte because of signed vs.
//! unsigned. For example, 0xffffff80 is not valid as an unsigned value but is valid as a signed value (-128).
//!
//! @hideinitializer

#if defined(_DEBUG)

#define ASSERT_MEMSET_VALID(d, v) _assert_memset_valid_imp(sizeof(*(d)), v, __FILE__, __LINE__)

//! @internal
//!

inline void _assert_memset_valid_imp(int size, signed v, char const * file, int line)
{
    if (!(((v >= -128) && (v <= 255)) && ((size == 1) || (v == 0) || (v == -1))) && AfxAssertFailedLine(file, line))
        AfxDebugBreak();
}

//! @internal
//!

inline void _assert_memset_valid_imp(int size, unsigned v, char const * file, int line)
{
    if (!(((v >= 0) && (v <= 255)) && ((size == 1) || (v == 0))) && AfxAssertFailedLine(file, line))
        AfxDebugBreak();
}

#else // defined ( _DEBUG )

#define ASSERT_MEMSET_VALID(d, v)

#endif // defined(_DEBUG)

//! This macro asserts that a pointer is valid
//!
//! @param	p	Pointer value to check
//!	@param	n	If true, 0 is accepted as a valid value, otherwise it is not. This is regardless of whether 0 is
//!				actually a valid address or not.
//!
//! @hideinitializer

#if defined(_DEBUG)

#define ASSERTP(p, n)                                                       \
    do                                                                      \
    {                                                                       \
        if (!((n) || (p) != 0) && AfxAssertFailedLine(THIS_FILE, __LINE__)) \
        {                                                                   \
            AfxDebugBreak();                                                \
        }                                                                   \
    } while (0)

#else // defined ( _DEBUG )

#define ASSERTP(p, n)

#endif // defined(_DEBUG)

//! This macro asserts that the @e relative difference between @a x and @a y is less than @a e.
//!
//! @param	x,y		Values being compared. @a x should not be 0.
//! @param	e		Maximum relative difference
//!
//! @note The actual difference between @a x and @a y must be less than @a x * @a e.
//!
//! @hideinitializer

#if defined(_DEBUG)

#include <cmath>

#define ASSERT_ALMOST_EQUAL(x, y, e)                                                       \
    do                                                                                     \
    {                                                                                      \
        if (!((x) == (y) || (abs((x) - (y)) / std::max(abs(x), abs(y)) <= abs(e))) && AfxAssertFailedLine(THIS_FILE, __LINE__)) \
        {                                                                                  \
            AfxDebugBreak();                                                               \
        }                                                                                  \
    } while (0)

#else // defined ( _DEBUG )

#define ASSERT_ALMOST_EQUAL(x, y, e)

#endif // defined(_DEBUG)

//! This macro asserts that @a i is a valid array index for the array @a a.
//!
//! @warning @a a must be declared as an array.
//!
//! @param	a	Array. @a must be declared as an array
//! @param	i	Index to check
//!
//! @hideinitializer

#if defined(_DEBUG)

#define ASSERT_ARRAY_INDEX_VALID(a, i)                                                       \
    do                                                                                       \
    {                                                                                        \
        if (!(0 <= (i) && (i) < elementsof(a)) && AfxAssertFailedLine(THIS_FILE, __LINE__))  \
        {                                                                                    \
            AfxDebugBreak();                                                                 \
        }                                                                                    \
    } while (0)

#else // defined ( _DEBUG )

#define ASSERT_ARRAY_INDEX_VALID(a, i)

#endif // defined(_DEBUG)

//! This macro asserts that @a i is non-negative, and 0 or a power of two
//!
//! @param	i	Value to check.
//!
//! @hideinitializer

#if defined(_DEBUG)

#define ASSERT_POWER_OF_TWO(i)                                                               \
    do                                                                                       \
    {                                                                                        \
        if (!(i >= 0 && ((i) & ((i) - 1)) == 0) && AfxAssertFailedLine(THIS_FILE, __LINE__)) \
        {                                                                                    \
            AfxDebugBreak();                                                                 \
        }                                                                                    \
    } while (0)

#else // defined ( _DEBUG )

#define ASSERT_POWER_OF_TWO(i)

#endif // defined(_DEBUG)
