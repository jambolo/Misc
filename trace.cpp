#if defined(_DEBUG)

#include "misc/trace.h"

#include <cstdarg>
#include <cstdio>
#include <windows.h>

// Maximum size of output string (including terminator) per call.
static size_t const BUFFER_SIZE = 1024;

void trace(char const * format, ...)
{
    char text[BUFFER_SIZE];

    va_list args;
    va_start(args, format);

    _vsnprintf(text, sizeof(text) - 1, format, args);
    text[sizeof text - 1] = 0; // Ensure that text is 0 terminated

    va_end(args);

    OutputDebugString(text);
}

#endif // defined( _DEBUG )
