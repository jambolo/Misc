#pragma once

#if !defined(MISC_COMMANDLINELIST_H)
#define MISC_COMMANDLINELIST_H

#include <string>
#include <vector>

//! Parses an array of pointers to strings and or a string with whitespace into an array of tokens.
//!
//! Standard command line wildcards are supported.
class CommandLineList
{
public:

    //! Constructor.
    //!
    //! @param  commandLine     Command line as a single string
    CommandLineList(char const * commandLine);

    //! Constructor.
    //!
    //! @param  argc    argc parameter
    //! @param  argv    argv parameter
    CommandLineList(int argc, char ** argv);

    //! Expands an arg and add the result to the list.
    //!
    //! If the arg can't be expanded or contains no wildcards, it is added as is.
    //!
    //! @param  arg     argument string
    void include(char const * arg);

    //! Returns the number of parsed command line tokens.
    size_t argc() const { return args_.size(); }

    //! Returns the parsed command line tokens.
    std::vector<std::string> args() const { return args_; }

private:
    std::vector<std::string> args_;
};

#endif // !defined(MISC_COMMANDLINELIST_H)
