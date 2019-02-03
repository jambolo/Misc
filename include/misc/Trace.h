#pragma once

#if !defined(trace_h__)
#define trace_h__

//! Outputs to the debugger only in a DEBUG build.
//!
//! When compiling a debug version, the trace function outputs to the debugger. The parameters and format string
//! are the same as printf().
//!
//! When compiling a release version, the trace call is optimized out. It is a clever hack. For example, the
//! statement @code
//!
//!     trace( "%d\n", x ); @endcode
//! is changed by the preprocessor to @code
//!
//!     0 && __BiteMe__( "%d\n", x ); @endcode
//! The compiler optimizes the statement to nothing. The parameters are not evaluated because of C's early out
//! functionality.
//!
//! @param	format	<tt>printf</tt>-style format string
//! @param	...		parameters
//!
//! @note	The size of the output is limited to 1024 bytes at a time.
//! @note	If you are using MFC, you should use the MFC TRACE() functions, instead of trace().

#if defined(_DEBUG)

void trace(char const * format, ...);

#else // defined( _DEBUG )

// Release version is optimized away

#define trace 0 && __BiteMe__
inline int __BiteMe__(char const *, ...) { return 0; }

#endif // defined(_DEBUG)

#endif // !defined(trace_h__)
