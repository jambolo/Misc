#pragma once

#if !defined(MISC_CLOCK_H)
#define MISC_CLOCK_H

#include "Misc/Singleton.h"
#include <cstdint>

//! A Singleton class that keeps track of the time

class [[deprecated("Use std:chrono instead")]] Clock : public Singleton<Clock>
{
public:

    //! Returns a reference to the only instance of Clock
    static Clock & instance();

    //! Returns the current time (in ticks)
    int64_t time() const;

    //! Returns the time elapsed since the given time (can be < 0)
    int64_t elapsedSince(int64_t start) const;

    //! Returns true if the current time is later than the specified time
    bool isPast(int64_t end) const;

    //! Converts ticks to seconds
    double toSeconds(int64_t ticks) const;

    //! Converts seconds to ticks
    int64_t toTicks(double seconds) const;

    //! Returns the clock tick frequency (ticks per second)
    int64_t frequency() const { return frequency_; }

    //! Returns the interval between ticks (in seconds)
    double interval() const { return interval_; }

private:

    // Constructor and destructor are private to prevent external construction and destruction
    Clock();
    ~Clock() = default;

    int64_t frequency_;                // Clock tick frequency
    double interval_;                  // Clock tick interval (1/frequency)
};

//! @param	start	Start time
//!
//! @return			Ticks since start time

inline int64_t Clock::elapsedSince(int64_t start) const
{
    return time() - start;
}

//! @param	end		End time
//!
//! @return			@c true, if the current time is past the end time

inline bool Clock::isPast(int64_t end) const
{
    return elapsedSince(end) > 0;
}

//! @param	ticks	Number of ticks
//!
//! @return		Value in seconds
//!
//! @warning	The precision of the returned value is limited to the precision of @c double, which is less than
//!				the precision of of the @c ticks value.

inline double Clock::toSeconds(int64_t ticks) const
{
    return double(ticks) * interval_;
}

//! @param	seconds	Number of seconds
//!
//! @return		Value in ticks
//!
//! @warning	The precision of the returned value is limited to the precision of double, which is less than
//!				the precision of of the return value.

inline int64_t Clock::toTicks(double seconds) const
{
    return int64_t(seconds / interval_ + 0.5);
}

#endif // !defined(MISC_CLOCK_H)
