#include "FrameRateCalculator.h"

#include <chrono>

using namespace std::chrono;
using namespace std::chrono_literals;

FrameRateCalculator::FrameRateCalculator()
    : nFrames_(0)
    , frameRate_(0.0f)
    , averageFrameRate_(0.0f)
{
    oldTime_ = oldTime2_ = high_resolution_clock::now();
}

//!
//! @param	t	Time of current frame

void FrameRateCalculator::update(high_resolution_clock::time_point t)
{
    auto dt = t - oldTime_;             // Time since previous update

    // Update the frame rate value
    if (dt > 0s)
        frameRate_ = 1.0f / duration<float, seconds::period>(dt).count();
    else
        frameRate_ = 0.0f;

    oldTime_ = t;  // Save the current time for next time

    // If 1 second has passed, compute the new average FPS value and reset the counters

    ++nFrames_;
    auto dt2 = t - oldTime2_;           // Time since previous 1 second update
    if (dt2 > 1s)
    {
        averageFrameRate_ = (float)nFrames_ / duration<float, seconds::period>(dt2).count();

        oldTime2_ = t; // Save the current time for next time
        nFrames_  = 0; // Reset the frame counter
    }
}
