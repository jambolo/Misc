#pragma once

#if !defined(MISC_ASSERTX_H)
#define MISC_ASSERTX_H

#if defined(_DEBUG)

#include <Misc/Etc.h>

#include <cassert>
#include <Crtdbg.h>
#include <windows.h>

#endif // defined(_DEBUG)

//! @name	Asserts
//!
//! This file contains the following assertions:
//!		- assert_limits( l, v, h )			asserts that l <= v <= h
//!		- assert_memset_valid( d, v )		asserts that memset( d, v, n ) is valid
//!		- assert_pointer_valid( p, n )		asserts that p is a valid pointer
//!		- assert_almost_equal( x, y, e )	asserts that fabs( ( x - y ) / x ) < e
//!		- assert_array_index_valid( a, i )	asserts that 0 <= i < elementsof( a )
//!		- assert_power_of_two( i )			asserts that i is a power of 2 or 0
//!		- assert_aligned( v, n )			asserts that v is a multiple of n
//!
//@{

#if defined(_DEBUG)

namespace
{
inline bool non_standard_assert_display(char const * text, char const * file, int line)
{
    if (_CrtDbgReport(_CRT_ERROR, file, line, NULL, text))
        _CrtDbgBreak();

    return true;
}

inline void assert_memset_valid_imp(size_t size, signed v, char const * file, int line)
{
    if (((v < -128) || (v > 127)) || ((size != 1) && (v != 0) && (v != -1)))
    {
        if (_CrtDbgReport(_CRT_ERROR, file, line, NULL, "Invalid memset parameters"))
            _CrtDbgBreak();
    }
}

inline void assert_memset_valid_imp(size_t size, unsigned v, char const * file, int line)
{
    if ((v > 255) || ((size != 1) && (v != 0)))
    {
        if (_CrtDbgReport(_CRT_ERROR, file, line, NULL, "Invalid memset parameters"))
            _CrtDbgBreak();
    }
}

inline void assert_pointer_valid_imp(void const * p, bool null_is_valid, wchar_t const * file, int line, wchar_t const * text)
{
    if (((p == nullptr) && !null_is_valid) ||
        ((p != nullptr) && (IsBadReadPtr(p, 1) || IsBadWritePtr((LPVOID)p, 1) || IsBadCodePtr((FARPROC)p))))
    {
        _wassert(text, file, line);
    }
}
} // anonymous namespace

#endif // defined(_DEBUG)

//! This macro asserts that @a v is between @a l and @a h (inclusive)
//!
//! @param	l,h		Upper and lower limits. @a l must be <= @a h.
//! @param	v		Value to check
//!
//! @hideinitializer

#if defined(_DEBUG)

#define assert_limits(l, v,                                                                                                          \
                      h) (void)(((l) <= (v) && (v) <= (h)) ||                                                                        \
                                (_wassert(_CRT_WIDE(#l) L" <= " _CRT_WIDE(#v) L" <= " _CRT_WIDE(#h), _CRT_WIDE(__FILE__), __LINE__), \
                                 0))

#else // defined ( _DEBUG )

#define assert_limits(l, v, h) ((void)0)

#endif // defined(_DEBUG)

//! This macro asserts that a call to memset with the specified value and destination will work as expected.
//!
//! @param	d	Destination address
//! @param	v	Value to be set
//!
//! The problem with memset is that it sets @b byte values but does not check the destination to make sure that it
//! is an array of bytes or that the value being set fits in a byte.
//!
//! This assert checks if the value being set fits in a byte. It also makes sure that if the size of the
//! destination elements is > 1, then the value being set is 0 or -1. Only 0 and -1 will work as expected if the
//! size of the destination elements is more than 1 byte.
//!
//! @note	Unfortunately, this assert cannot catch all cases of the value fitting in a byte because of signed
//!			vs. unsigned. For example, 0xffffff80 is not valid as an unsigned value but is valid as a
//!			@c signed value (-128).
//!
//! @hideinitializer

#if defined(_DEBUG)

#define assert_memset_valid(d, v) assert_memset_valid_imp(sizeof(*(d)), v, __FILE__, __LINE__)

#else // defined ( _DEBUG )

#define assert_memset_valid(d, v) ((void)0)

#endif // defined(_DEBUG)

//! This macro asserts that a pointer is valid
//!
//! @param	p	Pointer value to check
//!	@param	n	If true, 0 is accepted as a valid value, otherwise it is not. This is regardless of whether 0 is
//!				actually a valid address or not.
//!
//! @hideinitializer

#if defined(_DEBUG)

#define assert_pointer_valid(p, n) \
    assert_pointer_valid_imp(p, n, _CRT_WIDE(__FILE__), __LINE__, _CRT_WIDE(#p) L" is a valid pointer")

#else // defined ( _DEBUG )

#define assert_pointer_valid(p, n) ((void)0)

#endif // defined(_DEBUG)

//! This macro asserts that the @e relative difference between @a x and @a y is less than @a e.
//!
//! @param	x		Value to compare.
//! @param	y		Value to compare
//! @param	e		Maximum relative difference
//!
//! @note The actual difference between @a x and @a y must be less than @a x * @a e.
//!
//! @hideinitializer

#if defined(_DEBUG)

#include <cmath>

#define assert_almost_equal(x, y, e)               \
    (void)((fabs((x) - (y)) >= fabs((e) * (x))) || \
           (_wassert(_CRT_WIDE(#x) L" == " _CRT_WIDE(#y), _CRT_WIDE(__FILE__), __LINE__), 0))

#else // defined ( _DEBUG )

#define assert_almost_equal(x, y, e) ((void)0)

#endif // defined(_DEBUG)

//! This macro asserts that @a i is a valid array index for the array @a a.
//!
//! @param	a	Array. @a must be declared as an array
//! @param	i	Index to check
//!
//! @warning @a a must be declared as an array.
//!
//! @hideinitializer

#if defined(_DEBUG)

#define assert_array_index_valid(a, i)                                               \
    (void)((0 <= (i) && (i) < (int)elementsof(a)) ||                                 \
           (_wassert(L"0 <= " _CRT_WIDE(#i) L" <= elementsof( " _CRT_WIDE(#a) L" )", \
                     _CRT_WIDE(__FILE__), __LINE__), 0))

#else // defined ( _DEBUG )

#define assert_array_index_valid(a, i) ((void)0)

#endif // defined(_DEBUG)

//! This macro asserts that @a i is 0 or a power of two
//!
//! @param	i	Value to check.
//!
//! @hideinitializer

#if defined(_DEBUG)

#define assert_power_of_two(i)       \
    (void)(((i) & ((i) - 1)) == 0 || \
           (_wassert(_CRT_WIDE(#i) L" is a power of two or 0", _CRT_WIDE(__FILE__), __LINE__), 0))

#else // defined ( _DEBUG )

#define assert_power_of_two(i) ((void)0)

#endif // defined(_DEBUG)

//! This macro asserts that @a v is aligned on a boundary of @a n
//!
//! @param	v	Value to check
//! @param	n	Alignment value
//!
//! @hideinitializer

#if defined(_DEBUG)

#define assert_aligned(v, n)                                                                            \
    (void)((v) % (n) == 0 ||                                                                            \
           (_wassert(_CRT_WIDE(#v) L" is aligned on a boundary of " _CRT_WIDE(#n), _CRT_WIDE(__FILE__), \
                     __LINE__), 0))

#else // defined ( _DEBUG )

#define assert_aligned(v, n) ((void)0)

#endif // defined(_DEBUG)

//@}

#endif // !defined(MISC_ASSERTX_H)
