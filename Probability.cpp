#include "Probability.h"

//! @param  x       X
//!
//! @warning    Bad things can happen if not 0 <= x <= 20.
int64_t factorial(int64_t x)
{
    int64_t result = 1;
    while (x > 1)
    {
        result *= x--;
    }
    return result;
}

//! @param 	n   N
//! @param 	r   R
//!
//! @warning    Bad things can happen if not 0 <= r <= n <= 20.
int64_t permutations(int64_t n, int64_t r)
{
    // Computed as n * (n - 1) * (n - 2) * ... * (n - r + 1)
    int64_t last = n - r + 1;
    int64_t x = 1;
    while (n >= last)
    {
        x *= n--;
    }
    return x;
}

//! @param 	n   N
//! @param 	k   K
//!
//! @warning    Bad things can happen if not 0 <= k <= n <= 20.
int64_t combinations(int64_t n, int64_t k)
{
    // Note that there is a symmetry that allows some minor optimization.
    if (k <= n - k)
        return permutations(n, k) / factorial(k);
    else
        return permutations(n, n - k) / factorial(n - k);
}

//! @param 	n   N
//! @param 	k   K
//!
//! @warning    Bad things can happen if not 0 <= k <= 20 and 1 <= n.
int64_t multisets(int64_t n, int64_t k)
{
    // Computed as n * (n + 1) * (n + 2) * ... * (n + k - 1) / k!
    int64_t last = n + k - 1;
    int64_t x = 1;
    while (n <= last)
    {
        x *= n++;
    }
    return x / factorial(k);
}
