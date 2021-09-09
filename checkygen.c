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

typedef struct node
{
	int ln;
	char * fl;
	struct node * next;
} nd;

checkygenlist
create_checkygenlist ( void )
{
	nd  * head;
	unsigned long sz = sizeof ( nd );
	head = ( nd * ) malloc ( sz );
	OGL ( head );
	head->ln   = 0;
	head->fl   = NULL;
	head->next = NULL;
head_label:
	return head;
}

int
push_checkygennode ( checkygenlist l, int ln, const char * fl )
{
	nd * head;
	nd * entry;
	unsigned long sz = sizeof ( char ) * ( strlen ( fl ) + 1 );
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

int
remove_checkygenlist ( checkygenlist l )
{
	nd * pos = l;

	while ( pos != NULL )
	{
		nd * nxt = pos->next;
		free ( pos->fl );
		free ( pos );
		pos = nxt;
	}

	return 0;
}

