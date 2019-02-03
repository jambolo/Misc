#include "CommandLineList.h"

#include <string>
#if defined(WIN32)
#include <windows.h>
#else
#include <glob.h>
#endif

CommandLineList::CommandLineList(char const * commandLine)
{
    bool        in_arg        = false;      // true if processing an arg
    bool        in_quoted_arg = false;      // true if the current arg is quoted
    std::string arg;

    // Scan the command line for args and add them to the list. Whitespace is ignored inside quoted args.

    for (char const * p = commandLine; *p != 0; p++)
    {
        char const c = *p;

        // Continue to append chars until white space (or a double quote for quoted args) is found. When the end of the arg is
        // found, add it to the command line list
        if (in_arg)
        {
            if ((!in_quoted_arg && isspace(c)) || (in_quoted_arg && c == '"'))
            {
                // Add it to the list
                include(arg.c_str());

                // Clear the arg now that it is added
                in_arg = false;
                arg.clear();
            }
            else
            {
                arg += c;
            }
        }

        // Otherwise, if we aren't in an arg, then skip white space until the next arg is found

        else
        {
            // If a new arg is found, set everything up for the next arg

            if (!isspace(c))
            {
                in_arg        = true;
                in_quoted_arg = (c == '"');

                // Save the first char if it isn't a quote
                if (!in_quoted_arg)
                    arg += c;
            }
        }
    }

    // If the end of the string was reached while processing an arg, then 'arg' will contain the arg being processed. It must be
    // added to the list now.

    if (arg.size() > 0)
        include(arg.c_str());
}

CommandLineList::CommandLineList(int argc, char ** argv)
{
    // Extract command

    args_.push_back(*argv);
    ++argv;
    --argc;

    // Parse the rest of the command line

    while (argc > 0)
    {
        include(*argv);
        ++argv;
        --argc;
    }
}

void CommandLineList::include(char const * arg)
{
#if defined(WIN32)
    // Validate the length of the arg. FindFirstFile cannot handle strings
    // longer than MAX_PATH. If the string is too long then add it as is.

    if (strlen(arg) >= MAX_PATH)
    {
        args_.push_back(arg);
        return;
    }

    // Check if the arg has any wildcards. If it does, then search for files.
    // Otherwise just add it as is.

    if (strpbrk(arg, "*?") != NULL)
    {
        // Get the directory path because the find file function return only
        // file names.

        char drive[_MAX_DRIVE], dir[_MAX_DIR];
        _splitpath(arg, drive, dir, NULL, NULL);

        // Set up the find file stuff and get the first file

        int count = 0;
        WIN32_FIND_DATA find_data;

        HANDLE handle = FindFirstFile(arg, &find_data);

        // If a file is found, repeatedly add the found file to the list and find
        // another until there are no more.
        // Otherwise, don't add anything.

        if (handle != INVALID_HANDLE_VALUE)
        {
            do
            {
                // Add the reconstructed path to the list
                char path_buffer[_MAX_PATH];

                _makepath(path_buffer, drive, dir, find_data.cFileName, NULL);
                args_.push_back(path_buffer);
            } while (FindNextFile(handle, &find_data) != FALSE);
        }

        FindClose(handle);
    }
    else
    {
        args_.push_back(arg);
    }
#else
    if (strpbrk(arg, "*?["))
    {
        glob_t buffer;
        if (glob(arg, GLOB_NOCHECK, nullptr, &buffer))
        {
            for (char ** p = buffer.gl_pathv; *p; ++p)
            {
                args_.push_back(*p);
            }
            globfree(&buffer);
        }
        else
        {
            args_.push_back(arg);
        }
    }
    else
    {
        args_.push_back(arg);
    }
#endif
}
