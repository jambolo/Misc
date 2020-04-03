#if !defined(MISC_ETC_H_INCLUDED)
#define MISC_ETC_H_INCLUDED
#pragma once

#include <string>

//! @name Miscellaneous
//!
//@{

//! Returns number of elements in the array a.
//!
//! @param	a	Array
//!
//! @hideinitializer

template <typename T, int N>
int elementsof(T const (&a)[N])
{
    (void)a;
    return N;
}

namespace std
{
//! A Unicode-selectable string type.

#if defined(_UNICODE)
using tstring = wstring;
#else // defined( _UNICODE )
using tstring = string;
#endif // defined(_UNICODE)
} // namespace std

//! Converts the value of a compile-time symbol to a string at compile-time.
//!
//!
//! @hideinitializer

#define STRINGIZE(something)        STRINGIZE_HELPER(something)
#define STRINGIZE_HELPER(something) #something

//@}

#endif // !defined(MISC_ETC_H_INCLUDED)
