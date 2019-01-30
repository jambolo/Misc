#include "Timer.h"

#include "Clock.h"

Timer::Timer()
{
    // Start the timer immediately. This does not create a problem if it is explicitly started again later. It
    // prevents problems that would be caused by calling Stop or Resume without having called Start first.

    start();
}

//! @return		The start time
//!
//! @note	If the timer is already running, then the timer is reset.

int64_t Timer::start()
{
    startTime_ = stopTime_ = Clock::instance().time();
    running_   = true;

    return startTime_;
}

//! @return		The elapsed time
//!
//! @note	If the timer is note running, this function does nothing.

int64_t Timer::stop()
{
    if (running_)
    {
        stopTime_ = Clock::instance().time();
        running_  = false;
    }

    return elapsed();
}

//! This function continues timing again, but the time elapsed between the previous stop and the current time is
//! not included.
//!
//! @return		The current time
//!
//! @note	If the timer is already running, this function does nothing.

int64_t Timer::resume()
{
    int64_t currentTime = Clock::instance().time();

    if (!running_)
    {
        startTime_ += currentTime - stopTime_;
        running_    = true;
    }

    return currentTime;
}

//! If the timer is running, the time since the timer was started is returned. Otherwise, the elapsed time between
//! start and stop is returned.
//!
//! @return		Elapsed time

int64_t Timer::elapsed()
{
    int64_t elapsedTime;

    if (running_)
        elapsedTime = Clock::instance().elapsedSince(startTime_);
    else
        elapsedTime = stopTime_ - startTime_;

    return elapsedTime;
}
