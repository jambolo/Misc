/*****************************************************************************

                             CommandLineList.cpp

						Copyright 2001, John J. Bolton
	----------------------------------------------------------------------

	$Header: //depot/Libraries/CommandLineList/CommandLineList.cpp#2 $

	$NoKeywords: $

*****************************************************************************/

#include "CommandLineList.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>


/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

CommandLineList::CommandLineList( char const * pCommandLine )
{
	bool		in_arg			= false;	// true if processing an arg
	bool		in_quoted_arg	= false;	// true if the current arg is quoted
	std::string	arg;

	// Scan the command line for args and add them to the list. Whitespace is
	// ignored inside quoted args.

	for ( char const * p = pCommandLine; *p != 0; p++ )
	{
		char const	c	= *p;

		// Continue to append chars until white space (or a double quote
		// for quoted args) is found. When the end of the arg is found, add it
		// to the command line list

		if ( in_arg )
		{
			if ( ( !in_quoted_arg && isspace( c ) ) ||
				 ( in_quoted_arg && c == '"' ) )
			{
				// Add it to the list

				Include( arg.c_str() );

				// Clear the arg now that it is added

				in_arg = false;
				arg.erase();
			}
			else
			{
				arg += c;
			}

		}

		// Otherwise, if we aren't in an arg, then skip white space until the next
		// arg is found

		else
		{
			// If a new arg is found, set everything up

			if ( !isspace( c ) )
			{
				in_arg			= true;
				in_quoted_arg	= ( c == '"' );

				// Save the first char if it isn't a quote

				if ( !in_quoted_arg )
					arg += c;
			}
		}
	}

	// If the end of the string was reached while processing an arg, then 'arg'
	// will contain the arg being processed. It must be added to the list now.

	if ( arg.size() > 0 )
		Include( arg.c_str() );
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

CommandLineList::CommandLineList( int argc, char const * const * argv )
{
	// Extract command

	push_back( std::string( *argv ) );
	++argv;
	--argc;

	// Parse the rest of the command line

	while ( argc > 0 )
	{
		Include( *argv );
		++argv;
		--argc;
	}
}



/********************************************************************************************************************/
/*																													*/
/*																													*/
/********************************************************************************************************************/

void CommandLineList::Include( char const *pArg )
{
	// Validate the length of the arg. FindFirstFile cannot handle strings
	// longer than MAX_PATH. If the string is too long then add it as is.

	if ( strlen( pArg ) >= MAX_PATH )
	{
		push_back( std::string( pArg ) );
		return;
	}

	// Check if the arg has any wildcards. If it does, then search for files.
	// Otherwise just add it as is.

	if ( strpbrk( pArg, "*?" ) != NULL )
	{
		// Get the directory path because the find file function return only
		// file names.

		char drive[ _MAX_DRIVE ], dir[ _MAX_DIR ]; 
		_splitpath( pArg, drive, dir, NULL, NULL );

		// Set up the find file stuff and get the first file

		int				count	= 0;
		WIN32_FIND_DATA	find_data;

		HANDLE handle = FindFirstFile( pArg, &find_data );

		// If a file is found, repeatedly add the found file to the list and find
		// another until there are no more.
		// Otherwise, don't add anything.

		if ( handle != INVALID_HANDLE_VALUE )
		{
			do 
			{
				// Add the reconstructed path to the list
				char path_buffer[ _MAX_PATH ];

				_makepath( path_buffer, drive, dir, find_data.cFileName, NULL );
				push_back( std::string( path_buffer ) );

			} while ( FindNextFile( handle, &find_data ) != FALSE );
		}

		FindClose( handle );
	}
	else
	{
		push_back( std::string( pArg ) );
	}
}
