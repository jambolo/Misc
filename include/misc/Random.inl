/** @file *//********************************************************************************************************

                                                      Random.inl

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Misc/Random.inl#12 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#include "Random.h"

#include <cfloat>
#include <cstdint>

//! Returns a random value the range [0,1).

template< >
RandomFloat:: Value RandomFloat::get ()
{
    // In order to prevent rounding to 1, we must only allow as much precision as a float can handle.
    // floats only have 24 bits of precision so we have a choice of which bits to use. In a 32-bit LCG, the most
    // random bits are somewhere around bit 23. Since a float's high-order bits are the most important, let's
    // use bits 22-0.
    // Note: The lower-order bits of values produced by a LCG are not random. Fortunately, in normal usage, the
    // lower bits of a float are not significant.

    int const PRECISION = FLT_MANT_DIG;                     // Bits of precision in a float mantissa
    uint32_t const MASK = (1 << PRECISION) - 1;             // Only bits that count

    return Value(Implementation::get() & MASK) /  Value(MASK + 1);
}

//! Returns a random value in the range [ @a x, @a y ).

template< >
RandomFloat:: Value RandomFloat::get (Value x, Value y)
{
    // get() returns [0,1) so this function must be specialized.
    return get() * (y - x) + x;
}

//!
//! @param	state	New state.

inline void MT::setState(State const & state)
{
    state_ = state;
}

inline MT::State const & MT::state () const
{
    return state_;
}

inline void MT::reloadElement(uint32_t * p0, uint32_t s1, uint32_t sm)
{
    uint32_t const s0 = *p0;

    *p0 = sm ^ ((s0 & 0x80000000U | s1 & 0x7fffffffU) >> 1) ^ (-(int)(s1 & 0x00000001) & A);
}
