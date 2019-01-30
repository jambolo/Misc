#include "FrameRateCalculator.h"

#include "Clock.h"

FrameRateCalculator::FrameRateCalculator()
    : nFrames_(0)
    , frameRate_(0.0f)
    , averageFrameRate_(0.0f)
{
    oldTime_ = oldTime2_ = Clock::instance().time();
}

//!
//! @param	t	Time of current frame in ticks

void FrameRateCalculator::update(int64_t t)
{
    Clock & clock = Clock::instance();          // Convenience

    int64_t dt  = t - oldTime_;            // Time since previous update
    int64_t dt2 = t - oldTime2_;           // Time since previous 1 second update

    // Update the frame rate value

    if (dt > 0)
        frameRate_ = float(1.0 / clock.toSeconds(dt));
    else
        frameRate_ = 0;

    oldTime_ = t;  // Save the current time for next time

    // Update the average frame rate

    ++nFrames_;

    // If 1 second has passed, compute the new average FPS value and reset the counters

    if (dt2 > clock.frequency())
    {
        averageFrameRate_ = (float)nFrames_ / (float)clock.toSeconds(dt2);

        oldTime2_ = t; // Save the current time for next time
        nFrames_  = 0; // Reset the frame counter
    }
}
