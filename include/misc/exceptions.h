/** @file *//********************************************************************************************************

                                                     exceptions.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Misc/exceptions.h#8 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

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
