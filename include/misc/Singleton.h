#pragma once

#if !defined(Singleton_h__)
#define Singleton_h__

//! Base class used to implement a Singleton pattern.
//!
//! This class is used to implement a Singleton pattern. In order to use this class, you must follow these steps:
//!
//!	Derive from this class privately.
//!
//!	Implement a function that returns the instance of the derived class and instantiates as follows (where @c T is
//! is the name of the derived class):
//! @code
//!			static T & T::Instance()
//!			{
//!				if ( !Singleton<T>::Instance() )
//!				{
//!					new T;	// Instantiate
//!				}
//!
//!				return *static_cast< T* >( Singleton<T>::Instance() );
//!			}
//! @endcode
//!
//! @param	T	Class that inherits from this class
//!
//!
template <class T>
class Singleton
{
protected:

    //! Returns the instance of this class, or 0 if it hasn't been instantiated yet
    static Singleton * Instance()
    {
        return instance_;
    }

    //! Constructor
    //
    //! The constructor simply saves the address of the instance. This marks the class as having been
    //! instantiated, as the value returned by Instance() is no longer 0.
    Singleton()
    {
        instance_ = this;
    }

    //! Destructor
    //
    //! The destructor marks the class as non-instantiated by setting the address of the instance back to 0.
    //!
    //! @warning This is not a virtual destructor, which is one reason why the class must be inherited privately.
    ~Singleton()
    {
        instance_ = nullptr;
    }

private:

    // Prevent copy and assignment
    Singleton(Singleton const &);
    Singleton operator = (Singleton const &);

    static Singleton * instance_; //!< The single instance
};

template <class T>
Singleton<T> * Singleton<T>::instance_ = nullptr;

#endif // !defined(Singleton_h__)
