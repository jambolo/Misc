#if !defined(MiSC_EXCEPTIONS_H_INCLUDED)
#define MiSC_EXCEPTIONS_H_INCLUDED
#pragma once

#include <stdexcept>
#include <string>

//! An exception to throw when a constructor fails

class ConstructorFailedException : public std::runtime_error
{
public:

    //! Constructor.
    //!
    //! @param	what_arg	Exception information text

    explicit ConstructorFailedException(char const * what_arg = "constructor failed") throw ()
        : std::runtime_error(what_arg)
    {
    }

    //! Constructor.
    //!
    //! @param	what_arg	Exception information text

    explicit ConstructorFailedException(std::string const & what_arg) throw ()
        : std::runtime_error(what_arg)
    {
    }

    virtual ~ConstructorFailedException() override = default;
};

#endif // !defined(MiSC_EXCEPTIONS_H_INCLUDED)
