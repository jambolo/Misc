#if !defined(MISC_DEFERRED_H_INCLUDED)
#define MISC_DEFERRED_H_INCLUDED
#pragma once

//! A type that knows if it has ever been given a value.
//!
//! @param  T    The type of the value
//!
//! @note   T must be CopyConstructible, CopyAssignable and DefaultConstructible
template <class T>
class Deferred
{
public:
    //! Constructor.
    Deferred() = default;

    //! Constructor.
    //!
    //! @param  value       Initialization value
    Deferred(T const & value)
        : value_(value)
        , deferred_(true)
    {
    }

    //! Copy constructor.
    //!
    //! @param  rhs       Copied value
    //!
    //! @note   Copying an unassigned value results in an unassigned value.
    Deferred(Deferred const & rhs) = default;

    //! Assignment operator.
    //!
    //! @param  rhs       Value to assign
    //!
    //! @note   Assigning an unassigned value results in an unassigned value.
    Deferred & operator =(Deferred const & rhs) = default;

    //! Assignment operator.
    //!
    //! @param  rhs       Value to assign
    Deferred & operator =(T const & rhs)
    {
        value_    = rhs;
        deferred_ = true;
        return *this;
    }

    //! Conversion operator.
    //!
    //! The object is implicitly converted to its value.
    operator T() const
    {
        return value_;
    }

    //! Returns true if the object has ever been given a value.
    bool deferred() const
    {
        return deferred_;
    }

    //! Returns the value (or the default value, if never given a value).
    T value() const
    {
        return value_;
    }

private:
    T value_       = T();
    bool deferred_ = false;
};

#endif // !defined(MISC_DEFERRED_H_INCLUDED)
