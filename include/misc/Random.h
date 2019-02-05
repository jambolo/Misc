#pragma once

#if !defined(Random_h__)
#define Random_h__

#include <cstddef>
#include <cstdint>
#include <random>
#include <limits>

//! A class that defines the standard interface for RNG classes.
//!
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
//!
//! @deprecated Use std::linear_congruential_engine instead.
//!
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
class [[deprecated("Use std::linear_congruential_engine<uint32_t> instead")]] LCG32
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
//!
//! @deprecated Use std::mt19937 instead.
//!
//! @note	This class is used to implement Random and cannot be instantiated by itself.

class [[deprecated("Use std::mt19937 instead")]] MT
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
//! @deprecated Use std::minstd_rand instead.
//!
//! @note	This class is used to implement Random and cannot be instantiated by itself.

using LCG [[deprecated("Use std::minstd_rand instead")]] = std::minstd_rand;

//! A LCG pseudo-random number generator that generates 32-bit unsigned ints.
//!
//! @deprecated Use std::uniform_int_distribution instead.
//!
//! @warning	If the parameter @a y to the single-parameter function operator()() is small, the result is not very random.
//! @warning	If the difference between the parameters @a x and @a y to the two-parameter function operator () () is small,
//!				the result is not very random.
//!
//! @note	See Random for interface details.

using Random [[deprecated("Use std::uniform_int_distribution instead")]] = IRandom<uint32_t, uint32_t, std::minstd_rand>;

//! Super-duper.
//!
//! @deprecated Use std::uniform_int_distribution instead.
//!
//! @warning	If the parameter @a y to the single-parameter function operator()() is small, the result is not very random.
//! @warning	If the difference between the parameters @a x and @a y to the two-parameter function operator()() is small,
//!				the result is not very random.
//!
//! @note	See Random for interface details.

using Random69 [[deprecated("Use std::uniform_int_distribution instead")]] = IRandom<uint32_t, uint32_t, std::minstd_rand>;

//! A Mersenne Twister pseudo-random number generator that generates 32-bit unsigned ints.
//!
//! @deprecated Use std::uniform_int_distribution instead.
//!
//! @note	See Random for interface details.

using RandomMT [[deprecated("Use std::uniform_int_distribution instead")]] = IRandom<uint32_t, uint32_t, std::mt19937>;

//! A LCG pseudo-random number generator that generates floats.
//!
//! @deprecated Use std::uniform_real_distribution<float> instead.
//!
//! @note    See Random for interface details, however there are small differences.

class [[deprecated("Use std::uniform_real_distribution<float> instead")]] RandomFloat
{
public:

    using Value          = float;                     //!< The type of the values returned by the RNG.
    using Seed           = typename std::minstd_rand::result_type;                     //!< The type of the seed value.
    using Implementation = std::minstd_rand;                     //!< The implementation class.
    using State          = typename std::minstd_rand::result_type; //!< The type of the state.

    //! Constructor.
    //!
    //! @param    seed        Initial seed.
    RandomFloat(Seed const & seed)
        : generator_(seed)
    {
    }

    //! Returns a random float value.
    Value operator ()()
    {
        std::uniform_real_distribution<float> range(-std::numeric_limits<float>::max(),
                                                     std::numeric_limits<float>::max());
        return range(generator_);
    }

    //! Returns a random float value in the range [ 0, @a y ).
    //!
    //! @param    y    Upper limit.
    Value operator ()(Value y)
    {
        std::uniform_real_distribution<float> range(0.0f, y);
        return range(generator_);
    }

    //! Returns a random float value in the range [ @a x, @a y ).
    //!
    //! @param    x    Lower limit.
    //! @param    y    Upper limit.
    Value operator ()(Value x, Value y)
    {
        std::uniform_real_distribution<float> range(x, y);
        return range(generator_);
    }

    //! Sets the state.
    //!
    //! @param    state    New state.
    void setState(State const & state)
    {
        generator_.seed(state);
    }

    //! Returns the state.
    [[deprecated]]
    State state() const
    {
        assert(false); // no longer supported
        return 1;
    }

private:
    std::minstd_rand generator_;
};

#endif // !defined(Random_h__)
