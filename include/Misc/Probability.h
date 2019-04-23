#if !defined(MISC_PROBABILITY_H)
#define MISC_PROBABILITY_H

#pragma once

#include <cstdint>

//! Computes x!.
int64_t factorial(int64_t x);

//! Computes nPr.
int64_t permutations(int64_t n, int64_t r);

//! Computes nCk.
int64_t combinations(int64_t n, int64_t k);

//! Computes "n multichoose k".
int64_t multisets(int64_t n, int64_t k);

#endif // !defined(MISC_PROBABILITY_H)
