#include "Clock.h"

#include "Exceptions.h"

#if defined(__APPLE__)
#define HAVE_MACH_TIMER
#include <mach/mach_time.h>
#endif

#if defined(_MSC_VER)
#define HAVE_WIN32_TIMER
#include <windows.h>
#endif

//!
//! @exception	std::bad_alloc	out of memory

Clock & Clock::instance()
{
    if (Singleton<Clock>::Instance() == 0)
        new Clock;

    return *static_cast<Clock *>(Singleton<Clock>::Instance());
}

//!
//! @exception	ConstructorFailedException	QueryPerformanceFrequency() failed

Clock::Clock()
{
#if defined(HAVE_MACH_TIMER)
    mach_timebase_info_data_t rate_nsec;
    mach_timebase_info(&rate_nsec);
    frequency_ = 1000000000LL * rate_nsec.numer / rate_nsec.denom;
#elif defined(HAVE_WIN32_TIMER)
    LARGE_INTEGER frequency;
    BOOL          ok;

    ok = QueryPerformanceFrequency(&frequency);
    if (ok == 0)
        throw ConstructorFailedException();

    frequency_ = frequency.QuadPart;
#else
#error unsupported
#endif
    interval_  = 1.0 / double(frequency_);
}

int64_t Clock::time() const
{
#if defined(HAVE_MACH_TIMER)
    return mach_absolute_time();
#elif defined(HAVE_WIN32_TIMER)
    LARGE_INTEGER time;
    QueryPerformanceCounter(&time);
    return time.QuadPart;
#else
#error unsupported
#endif
}
