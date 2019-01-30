#pragma once

#if !defined(MISC_TIMER_H)
#define MISC_TIMER_H

#include <cstdint>

//! A class that measures time durations

class Timer
{
public:

    //! Constructor
    Timer();

    //! Destructor
    ~Timer() = default;

    //! Starts the timer
    int64_t start();

    //! Stops the timer
    int64_t stop();

    //! Resumes the timer
    int64_t resume();

    //! Returns the elapsed time
    int64_t elapsed();

private:

    int64_t startTime_;    //!< Time at which the timer started
    int64_t stopTime_;     //!< Time at which the timer was stopped (if it is not running)
    bool running_;         //!< true if the timer is running
};

#endif // !defined(MISC_TIMER_H)
