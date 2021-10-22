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
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/*	checkygen.c	*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "checkygen.h"

/**
* @brief "node" samples information about a location (line ln, file fl) of a "TEST()" and points (next) to the next node
*/
typedef struct node
{
	int ln;
	char * fl;
	struct node * next;
} nd;

/**
* @brief "create_checkygenlist" creates a list to documents all the places (file and line) where "TEST()" will be found
*
* @return head of a checkygenlist
*/
checkygenlist
create_checkygenlist ( void )
{
	nd  * head = NULL;
	size_t sz = sizeof ( nd );
	head = ( nd * ) malloc ( sz );
	OGL ( head );
	head->ln   = 0;
	head->fl   = NULL;
	head->next = NULL;
head_label:
	return head;
}

/**
* @brief "push_checkygenlist" inserts a node with information about a "TEST()" found in line ln and file fl into list l
*
* @param l
* @param ln
* @param fl
*
* @return EXIT_VALUE
*/
int
push_checkygennode ( checkygenlist l, int ln, const char * fl )
{
	nd * head;
	nd * entry;
	size_t sz = sizeof ( char ) * ( strlen ( fl ) + 1 );
	entry = ( nd * ) malloc ( sizeof ( nd ) );
	OGL ( entry );
	head = l;
	entry->ln   = ln;
	char * s = malloc ( sz );
	OGL ( s );
	strcpy ( s, fl );
	entry->fl   = s;
	entry->next = head->next;
	head->next  = entry;
	return 1;
s_label:
	free ( entry );
entry_label:
	return 0;
}

/**
* @brief "find_checkygennode" signals if a "TEST()" at line ln in file fl is already listed in l
*
* @param l
* @param ln
* @param fl
*
* @return 1: YES / 0: No
*/
int
find_checkygennode ( checkygenlist l, int ln, const char * fl )
{
	nd * pos = l;

	while ( pos != NULL )
	{
		if ( pos->ln == ln && strcmp ( pos->fl, fl ) == 0 )
			return 1;

		pos = pos->next;
	}

	return 0;
}

/**
* @brief "remove_checkygenlist" deletes the list l
*
* @param l
*
* @return EXIT_VALUE
*/
int
remove_checkygenlist ( checkygenlist l )
{
	nd * pos = l;

	while ( pos != NULL )
	{
		nd * nxt = pos->next;

		if ( pos->fl != NULL )
			free ( pos->fl );

		free ( pos );
		pos = nxt;
	}

	return 0;
}

