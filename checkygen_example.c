/***************************************************************************
 *   Copyright (C) 2021 by Joachim Comes                                   *
 *   jcomes@prima-philosophia.org                                          *
 *                                                                         *
 *   This program is free software: you can redistribute it and/or modify  *
 *   it under the terms of the GNU Affero General Public License as        *
 *   published by the Free Software Foundation, either version 3 of the    *
 *   License, or (at your option) any later version.                       *
 *			                                                               *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU Affero General Public License for more details.                   *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, store to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/* checkygen_example.c */

/**
	\file checkygen_example.c
	\mainpage checkygen_example
	\section ce checkygen_example
	checkygen_example is a program which takes an integer argument as input and gives the return value "EXIT_SUCCESS" if
	the argument is a multiplee of two otherwise the return value is "EXIT_FAILURE".
	\section cg Checkygen
	checkygen_example is not very useful but allows to show some concepts of the test environment Checkygen
	\subsection ut Unit Testing
	For using Checkygen code has to include checkygen.h. checkygen.o is to link together with the other objects.
	A test needs a  macro "DECLARE_TEST" in front of the main function.
	It needs a macro "CREATE_TEST" just in the beginning of the main function and a macro "REMOVE_TEST" at the end of the
	main function.
	Each function to test starts with a macro "START_TEST" followed by instructions for each test case and macros
	"TEST(a)" which test if "a" is true.
	Behind those tests a macro "STOP_TEST" is needed.
	If the program starts in CHECKYGEN mode each test will be executed only one time. After this the tests are ignored.
	\subsection Pt Pretty Testing
	Checkygen allows to formulate all test cases within the functions to test. But Checkygen following the idea of Doxygen does not show the results only on stdout but exports the test results in a more pretty form. Results are incorporated
	into the Doxygen documentation.
	In the documentation of each function should be a "\note" for each test which describes given input, expected output and return value.
	In addition to this for all tests of a function should be a predefined doxyen macro "\WRN{...}" inside the function
	documentation: e.g. for the 5. test oft function foo() write"\WRN{foo_5}".
	Then a new Doxygen documentation made after the test run shows a warning in the description of the function,
	if the function failed.
	'./checkygen' itself is nothing but a simple bash script which inserts the warnings into the doxygen-documentation
	and runs doxygen.
*/

#include <stdio.h>
#include <stdlib.h>
#include "checkygen.h"

/* This macro declares the test environment */
/** \cond */
DECLARE_TEST
/** \endcond */

int multiple_of_two ( int, int * );

int
main ( int argc, char * * argv )
{

	/* This macro creates a test environment */
	CREATE_TEST

	int in = 0, out = 0;

	if ( argc == 2 )
		in = atoi ( argv[1] );

	multiple_of_two ( in, &out );
	printf ( "\n%d\n", out );

	/* This macro removes the test environment*/
	REMOVE_TEST

	return EXIT_SUCCESS;
}

/**
	\brief
	multiple_of_two() calculates out from in.

	@param in int in is the input

	@param out int * out points to the output

	multiple_of_two() has the return value EXIT_FAILURE if 'in%2 != 0'
	otherwise 'out==in/2
	\note
		test multiple_of_two1:\n
		given:\n
		in = 2\n
		expected:\n
		multiple_of_two() == EXIT_SUCCESS\n
		out == 1\n
	\WRN{multiple_of_two1}
	\note
		test multiple_of_two2:\n
		given:\n
		in = 1\n
		expected:\n
		multiple_of_two() == EXIT_FAILURE
	\WRN{multiple_of_two2}
*/
int
multiple_of_two ( int in, int * out )
{

	/* This macro starts the function tests */
	START_TEST

	int m, n;

	m = 2;
	/* This macro tests the function the 1. time*/
	TEST ( multiple_of_two ( m, &n ) == EXIT_SUCCESS && n == 1 );

	m = 1;
	/* This macro tests the function the 2. time*/
	TEST ( multiple_of_two ( m, &n ) == EXIT_FAILURE );

	/* This macro stops the function tests */
	STOP_TEST

	/* !!! bad implementation to show the effect of the test !!! */

	if ( in % 2 != 0 )
		return EXIT_FAILURE;

	*out = in / 3;

	return EXIT_SUCCESS;
}

