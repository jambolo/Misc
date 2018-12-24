#if !defined( COMMANDLINELIST_H_INCLUDED )
#define COMMANDLINELIST_H_INCLUDED

#pragma once

/*****************************************************************************

                              CommandLineList.h

						Copyright 2001, John J. Bolton
	----------------------------------------------------------------------

	$Header: //depot/Libraries/CommandLineList/CommandLineList.h#2 $

	$NoKeywords: $

*****************************************************************************/

#include <vector>
#include <string>

class CommandLineList : public std::vector< std::string >
{
public:
	CommandLineList( char const * pCommandLine );
	CommandLineList( int argc, char const * const * argv );

	// Expand an arg and add the result to the list. If the arg can't be
	// expanded or contains no wildcards, it is added as is.
	void Include( char const *pArg );
};

#endif // !defined( COMMANDLINELIST_H_INCLUDED )
