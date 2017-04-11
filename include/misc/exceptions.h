#pragma once

#if !defined(exceptions_h__)
#define exceptions_h__

#include <stdexcept>
#include <string>

//! An exception to throw when a constructor fails

class ConstructorFailedException : public std::runtime_error
{
public:

    // Constructor
    //!
    //! @param	what_arg	Exception information text

    ConstructorFailedException(char const * what_arg = "constructor failed") throw ()
        : std::runtime_error(what_arg)
    {
    }

    // Constructor
    //!
    //! @param	what_arg	Exception information text

    ConstructorFailedException(std::string const & what_arg) throw ()
        : std::runtime_error(what_arg)
    {
    }
};

#endif // !defined(exceptions_h__)
