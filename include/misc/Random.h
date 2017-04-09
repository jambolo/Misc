/** @file *//********************************************************************************************************

                                                       Random.h

                                            Copyright 2003, John J. Bolton
    --------------------------------------------------------------------------------------------------------------

    $Header: //depot/Libraries/Misc/Random.h#16 $

    $NoKeywords: $

********************************************************************************************************************/

#pragma once

#include <cstdint>

//! A class that defines the standard interface for RNG classes.
//
//! This class is used to standardize the interface of random number generator classes. This class is not normally
//! used directly.
//!
//! @param	V	The type of the values returned by the RNG.
//! @param	S	The type of the seed value.
//! @param	I	The implementation class.
//!
//! The I class must implement the following type:
//!		- @c State -	The state of the RNG. The state must contain enough information such that identical states
//!						will generate identical sequences.
//!
//! The I class must implement the following methods:
//!		- @c get -		Returns the next number in the sequence.
//!		- @c state -	Returns the current state.
//!		- @c setState -	Sets the state to the specified value.

template <typename V, typename S, typename I>
class IRandom : private I
{
public:

    typedef V Value;                                            //!< The type of the values returned by the RNG.
    typedef S Seed;                                             //!< The type of the seed value.
    typedef I Implementation;                                   //!< The implementation class.
    typedef typename Implementation::State State;               //!< The type of the state.

    //! Constructor.
    //
    //!
    //! @param	seed		Initial seed.
    IRandom(Seed seed)
        : Implementation(seed)
    {
    }

    //! Returns a random value that is implementation-specific.
    Value operator ()()
    {
        return Implementation::operator ()();
    }

    //! Returns a random value in the range [ 0, @a y ).
    //
    //!
    //! @param	y	Upper limit.
    Value operator ()(Value y)
    {
        return operator ()(0, y);
    }

    //! Returns a random value in the range [ @a x, @a y ).
    //
    //! @param	x	Lower limit.
    //! @param	y	Upper limit.
    Value operator ()(Value x, Value y)
    {
        return Implementation::operator ()() % (y - x) + x;
    }

    //! Sets the state.
    //
    //!
    //! @param	state	New state.
    void setState(State const & state)
    {
        Implementation::setState(state);
    }

    //! Returns the state.
    State const & state() const
    {
        return Implementation::state();
    }
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
//! @note	This class is used to implement IRandom and cannot be instantiated by itself.

template <int A, int B>
class LCG32
{
protected:

    typedef uint32_t Value;         //!< The type of the values returned by this RNG.
    typedef uint32_t Seed;          //!< The type of the seed value.
    typedef uint32_t State;         //!< The type of the state.

    enum
    {
        MIN = 0,                //!< Minimum value generated.
        MAX = 0xffffffffU       //!< Maximum value generated (M-1).
    };

    //! Constructor
    //
    //!
    //! @param	seed		Initial seed.
    LCG32(uint32_t seed)
        : seed_(seed)
    {
    }

    //! Returns a random value in the range [ @c MIN, @c MAX ).
    uint32_t operator ()()
    {
        //	m_Seed = static_cast< uint32_t >( ( A * static_cast< uint64 >( m_Seed ) + B ) % M );

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

    uint32_t seed_;                        // The seed.
};

//! A Mersenne Twister pseudo-random number generator implementation that generates 32-bit unsigned ints.
//
//!
//! @note	This class is used to implement IRandom and cannot be instantiated by itself.

class MT
{
public:
    static size_t const N     = 624;            //!< The number of elements in the state vector
    static uint32_t const MIN = 0;              //!< Minimum value generated.
    static uint32_t const MAX = 0xffffffffU;    //!< Maximum value generated (M-1).

    //! The state of the generator.
    struct State
    {
        uint32_t v[N];        //!< The state vector.
        int      index;       //!< The index into the state vector of the current value.
    };

protected:

    //!	Constructor
    MT(uint32_t seed);

    //!	Returns	a random value (@c MIN	<= operator () () < @c MAX).
    uint32_t operator ()();

    //!	Sets the state.
    void setState(State const & state);

    //! Returns the state.
    State const & state() const;

private:

    enum
    {
        M = 397,
        A = 0x9908b0dfU,
        B = 0x9d2c5680U,
        C = 0xefc60000U,
    };

    void reload();
    static void reloadElement(uint32_t * p0, uint32_t s1, uint32_t sm);

    State state_;      //!< The state of the generator.
};

//! A good LCG implementation.
//
//!
//! @note	This class is used to implement IRandom and cannot be instantiated by itself.

typedef LCG32<3039177861, 1>  LCG;

//! A LCG pseudo-random number generator that generates 32-bit unsigned ints.
//
//! @warning	If the parameter @a y to the single-parameter function operator()() is small, the result is not very random.
//! @warning	If the difference between the parameters @a x and @a y to the two-parameter function operator () () is small,
//!				the result is not very random.
//!
//! @note	See IRandom for interface details.

typedef IRandom<uint32_t, uint32_t, LCG>  Random;

//! Super-duper
//
//! @warning	If the parameter @a y to the single-parameter function operator()() is small, the result is not very random.
//! @warning	If the difference between the parameters @a x and @a y to the two-parameter function operator () () is small,
//!				the result is not very random.
//!
//! @note	See IRandom for interface details.

typedef IRandom<uint32_t, uint32_t, LCG32<69069, 1> >    Random69;

//! A Mersenne Twister pseudo-random number generator that generates 32-bit unsigned ints.
//!
//! @note	See IRandom for interface details.

typedef IRandom<uint32_t, uint32_t, MT>       RandomMT;

//! A LCG pseudo-random number generator that generates floats.
//!
//! @note	See IRandom for interface details, however there are small differences.

typedef IRandom<float, uint32_t, LCG> RandomFloat;

// Inline functions

#include "Random.inl"
