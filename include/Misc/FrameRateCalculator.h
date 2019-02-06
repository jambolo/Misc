#pragma once

#if !defined(MISC_FRAMERATECALCULATOR_H)
#define MISC_FRAMERATECALCULATOR_H

#include <chrono>

//! A class that keeps track of the frame rate.

class FrameRateCalculator
{
public:

    //! Constructor.
    FrameRateCalculator();

    //! Updates the state and computes the new frame rate values.
    void update(std::chrono::high_resolution_clock::time_point t);

    //! Returns the frame rate for the previous frame.
    float rate() const { return frameRate_; }

    //! Returns the average frame rate over the previous second.
    //!
    //! @note	This value is updated every second (at most).
    float average() const { return averageFrameRate_; }

private:

    std::chrono::high_resolution_clock::time_point oldTime_;    // Time of the previous update
    std::chrono::high_resolution_clock::time_point oldTime2_;   // Time of the previous 1-second update
    int nFrames_;                                               // Number of frames since the previous 1-second update
    float frameRate_;                                           // Frame rate of the previous frame
    float averageFrameRate_;                                    // Frame rate over the previous second
};

#endif // !defined(MISC_FRAMERATECALCULATOR_H)
