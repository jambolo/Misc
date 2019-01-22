#pragma once

#if !defined(PathName_h__)
#define PathName_h__

#include <locale>
#include <string>

//! A variation of @c std::char_traits for characters in a path name.
//!
//! The difference between these traits and <tt>std::char_traits< char ></tt> is that comparisons are
//! case-independent, and '\' and '/' are equivalent. This struct is used by the class PathName

struct char_traits_path_char : public std::char_traits<char>
{
    //! @name Overrides char_traits<char>
    //@{

    static bool __cdecl eq(char _Left, char _Right)
    {
        return _Left == _Right ||
               is_slash(_Left) && is_slash(_Right) ||
               std::toupper(_Left, std::locale()) == std::toupper(_Right, std::locale());
    }

    static bool __cdecl lt(char _Left, char _Right)
    {
        return (!is_slash(_Left) || !is_slash(_Right)) &&
               _Left std::toupper(_Left, std::locale()) < std::toupper(_Right, std::locale());
    }

    static bool __cdecl eq_int_type(const int_type & _Left, const int_type & _Right)
    {
        if (_Left == _Right)
            return true;

        if (!not_eof(_Left) || !not_eof(_Right))
            return false;

        return eq(to_char_type(_Left), to_char_type(_Right));
    }

    static int __cdecl compare(const char * _First1, const char * _First2, size_t _Count)
    {
        while (_Count > 0 && eq(*_First1, *_First2))
        {
            --_Count;
            ++_First1;
            ++_First2;
        }

        if (_Count <= 0)
            return 0;
        else if (lt(*_First1, *_First2))
            return -1;
        else
            return +1;
    }

    static const char * __cdecl find(const char * _First, size_t _Count, char _Ch)
    {
        while (_Count > 0 && !eq(*_First, _Ch))
        {
            --_Count;
            ++_First;
        }

        if (_Count <= 0)
            return 0;
        else
            return _First;
    }

    //@}

    //! Returns @c true if the character is a slash or backslash
    //
    //!
    //! @param	c	character to test
    static bool is_slash(char c)
    {
        return c == '\\' || c == '/';
    }
};

//! A string useable for path names.
//
//!
//! This class differs from <tt>std::string</tt> in that comparisons are case-independent and '/' and '\' are
//! equivalent.

class PathName : public std::basic_string<char, char_traits_path_char>
{
};

#endif // !defined(PathName_h__)
