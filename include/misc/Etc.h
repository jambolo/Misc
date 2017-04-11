#pragma once

#if !defined(Etc_h__)
#define Etc_h__

#include <string>

//! @name Miscellaneous
//!
//@{

//! Returns number of elements in the array @a a.
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
typedef std::wstring tstring;
#else // defined( _UNICODE )
typedef std::string tstring;
#endif // defined( _UNICODE )
} // namespace std

//! Converts the value of a compile-time symbol to a string at compile-time.
//!
//!
//! @hideinitializer

#define STRINGIZE(something) STRINGIZE_HELPER(something)
#define STRINGIZE_HELPER(something) #something

//@}

#endif // !defined(Etc_h__)
