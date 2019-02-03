#pragma once

#if !defined(Random_h__)
#define Random_h__

#include <cstddef>
#include <cstdint>

//! A class that defines the standard interface for RNG classes.
//
//! This class is used to standardize the interface of random number generator classes.
//!
//! @param	V	The type of the values returned by the RNG.
//! @param	S	The type of the seed value.
//! @param	I	The implementation class.
//!
//! The I class must implement the following type:
//!		- State -	The state of the RNG. The state must contain enough information such that identical states
//!						will generate identical sequences.
//!
//! The I class must implement the following methods:
//!		- operator () -	Returns the next number in the sequence.
//!		- state -	    Returns the current state.
//!		- setState -	    Sets the state to the specified value.

template <typename V, typename S, typename I>
class IRandom
{
public:

    using Value          = V;                     //!< The type of the values returned by the RNG.
    using Seed           = S;                     //!< The type of the seed value.
    using Implementation = I;                     //!< The implementation class.
    using State          = typename Implementation::State; //!< The type of the state.

    //! Constructor.
    //!
    //! @param	seed		Initial seed.
    IRandom(Seed const & seed)
        : implementation_(seed)
    {
    }

    //! Returns a random value that is implementation-specific.
    Value operator ()()
    {
        return implementation_();
    }

    //! Returns a random value in the range [ 0, @a y ).
    //!
    //! @param	y	Upper limit.
    Value operator ()(Value y)
    {
        return operator ()(0, y);
    }

    //! Returns a random value in the range [ @a x, @a y ).
    //!
    //! @param	x	Lower limit.
    //! @param	y	Upper limit.
    Value operator ()(Value x, Value y)
    {
        return implementation_() % (y - x) + x;
    }

    //! Sets the state.
    //!
    //! @param	state	New state.
    void setState(State const & state)
    {
        implementation_.setState(state);
    }

    //! Returns the state.
    State state() const
    {
        return implementation_.state();
    }

private:
    Implementation implementation_;
};

//! A LCG pseudo-random number generator implementation template that generates 32-bit unsigned ints.
//
//! @param	A	Multiplier
//! @param	B	Offset
//!
//! A LCG (Linear Congruential Generator) generates a sequence of pseudo-random numbers using the following formula:
//!
//! seed[i] = ( A * seed[i-1] + B ) mod M
//!
//! In this implementation of an LCG, M is 2^32. This is a reasonable value, and it has the advantage that the
//! "mod M" operation is done automatically by the CPU when the other operations overflow.
//!
//! @note	This class is used to implement Random and is not designed be instantiated by itself.

template <uint32_t A, uint32_t B>
class LCG32
{
public:

    using Value = uint32_t; //!< The type of the values returned by this RNG.
    using Seed  = uint32_t; //!< The type of the seed value.
    using State = uint32_t; //!< The type of the state.

    enum
    {
        MIN = 0,          //!< Minimum value generated.
        MAX = 0xffffffffU //!< Maximum value generated (M-1).
    };

    //! Constructor
    //
    //!
    //! @param	seed		Initial seed.
    LCG32(uint32_t seed)
        : seed_(seed)
    {
    }

    //! Returns a random value in the range [ MIN, MAX ).
    uint32_t operator ()()
    {
        //	seed_ = static_cast< uint32_t >( ( A * static_cast< uint64 >( m_Seed ) + B ) % M );

        seed_ = A * seed_ + B;

        return seed_;
    }

    //! Sets the state.
    //
    //!
    //! @param	state	New state.
    void setState(uint32_t const & state)
    {
        seed_ = state;
    }

    //! Returns the state.
    uint32_t const & state() const
    {
        return seed_;
    }

private:

    uint32_t seed_; // The seed.
};

//! A Mersenne Twister pseudo-random number generator implementation that generates 32-bit unsigned ints.
//
//!
//! @note	This class is used to implement Random and cannot be instantiated by itself.

class MT
{
public:
    static size_t constexpr N     = 624;         //!< The number of elements in the state vector
    static uint32_t constexpr MIN = 0;           //!< Minimum value generated.
    static uint32_t constexpr MAX = 0xffffffff;  //!< Maximum value generated (M-1).

    //! The state of the generator.
    struct State
    {
        uint32_t v[N];  //!< The state vector.
        int index;      //!< The index into the state vector of the current value.
    };

    //!	Constructor.
    MT(uint32_t seed);

    //!	Returns	a random value (MIN	<= operator () () < MAX).
    uint32_t operator ()();

    //!	Sets the state.
    void setState(State const & state) { state_ = state; }

    //! Returns the state.
    State state() const { return state_; }

private:

    static uint32_t const M = 397;
    static uint32_t const A = 0x9908b0df;
    static uint32_t const B = 0x9d2c5680;
    static uint32_t const C = 0xefc60000;

    void        reload();
    static void reloadElement(uint32_t * p0, uint32_t s1, uint32_t sm)
    {
        uint32_t const s0 = *p0;

        *p0 = sm ^ (((s0 & 0x80000000U) | (s1 & 0x7fffffffU)) >> 1) ^ (-(int)(s1 & 0x00000001) & A);
    }

    State state_; //!< The state of the generator.
};

//! A good LCG implementation.
//!
//!
//! @note	This class is used to implement Random and cannot be instantiated by itself.

using LCG = LCG32<3039177861, 1>;

//! A LCG pseudo-random number generator that generates 32-bit unsigned ints.
//!
//! @warning	If the parameter @a y to the single-parameter function operator()() is small, the result is not very random.
//! @warning	If the difference between the parameters @a x and @a y to the two-parameter function operator () () is small,
//!				the result is not very random.
//!
//! @note	See Random for interface details.

using Random = IRandom<uint32_t, uint32_t, LCG>;

//! Super-duper.
//!
//! @warning	If the parameter @a y to the single-parameter function operator()() is small, the result is not very random.
//! @warning	If the difference between the parameters @a x and @a y to the two-parameter function operator()() is small,
//!				the result is not very random.
//!
//! @note	See Random for interface details.

using Random69 = IRandom<uint32_t, uint32_t, LCG32<69069, 1>>;

//! A Mersenne Twister pseudo-random number generator that generates 32-bit unsigned ints.
//!
//! @note	See Random for interface details.

using RandomMT = IRandom<uint32_t, uint32_t, MT>;

//! A LCG pseudo-random number generator that generates floats.
//!
//! @note	See Random for interface details, however there are small differences.

using RandomFloat = IRandom<float, uint32_t, LCG>;

// Inline functions

#include <cfloat>
#include <cstdint>

//! Returns a random value the range [0,1).

template <>
inline RandomFloat::Value RandomFloat::operator ()()
{
    // In order to prevent rounding to 1, we must only allow as much precision as a float can handle.
    // floats only have 24 bits of precision so we have a choice of which bits to use. In a 32-bit LCG, the most
    // random bits are somewhere around bit 23. Since a float's high-order bits are the most important, let's
    // use bits 22-0.
    // Note: The lower-order bits of values produced by a LCG are not random. Fortunately, in normal usage, the
    // lower bits of a float are not significant.

    int const      PRECISION = FLT_MANT_DIG;    // Bits of precision in a float mantissa
    uint32_t const MASK      = (1 << PRECISION) - 1; // Only bits that count

    return Value(implementation_() & MASK) / Value(MASK + 1);
}

//! Returns a random value in the range [ @a x, @a y ).

template <>
inline RandomFloat::Value RandomFloat::operator ()(Value x, Value y)
{
    // operator()() returns [0,1) so this function must be specialized.
    return operator ()() * (y - x) + x;
}

#endif // !defined(Random_h__)
