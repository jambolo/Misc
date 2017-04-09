/** @file *//********************************************************************************************************

                                                      Random.cpp

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Misc/Random.cpp#12 $

    $NoKeywords: $

********************************************************************************************************************/

#include "misc/Random.h"

//!
//! @param	seed	Initial seed.

MT::MT(uint32_t seed)
{
    // See MT19337ar

    uint32_t * const v = state_.v;     // Convenience

    v[0] = seed;
    for (int i = 1; i < N; i++)
    {
        v[i] = 1812433253UL * (v[i - 1] ^ (v[i - 1] >> 30)) + i;
    }

    reload();
}

uint32_t MT::get()
{
    if (state_.index >= N)
    {
        reload();
    }

    uint32_t y = state_.v[state_.index++];

    y ^= (y >> 11);
    y ^= (y <<  7) & B;
    y ^= (y << 15) & C;
    y ^= (y >> 18);

    return y;
}

void MT::reload()
{
    uint32_t * const v = state_.v;     // Convenience

    int j;
    uint32_t * p0;
    uint32_t * pM;

    p0 = &v[0];
    pM = &v[M];
    for (j = 0; j < N - M; j++)
    {
        reloadElement(p0, *(p0 + 1), pM[j]);
        ++p0;
    }

    p0 = &v[N - M];
    pM = &v[0];
    for (j = 0; j < M - 1; j++)
    {
        reloadElement(p0, *(p0 + 1), pM[j]);
        ++p0;
    }

    reloadElement(&v[N - 1], v[0], v[M - 1]);

    state_.index = 0;
}
