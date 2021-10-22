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

/* checkygen.h	*/

#ifndef CHECKYGEN_H

#define CHECKYGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <assert.h>

typedef struct node * checkygenlist;

checkygenlist create_checkygenlist ( void );
int    push_checkygennode ( checkygenlist, int, const char * );
int    find_checkygennode ( checkygenlist, int, const char * );
int  remove_checkygenlist ( checkygenlist );

extern checkygenlist checkygenfl;
extern FILE * checkygenfp;

/* Checkygen macros */

#define DECLARE_TEST checkygenlist checkygenfl = NULL; FILE * checkygenfp = NULL;

#ifdef CHECKYGEN
#define CREATE_TEST checkygenfl = create_checkygenlist(); if(checkygenfl==NULL) return EXIT_FAILURE; checkygenfp = fopen("Checkyfile","w"); if(checkygenfp==NULL) return EXIT_FAILURE; fprintf(checkygenfp,"EXTRACT_ALL = YES\nOPTIMIZE_OUTPUT_FOR_C = YES\nALIASES += WRN{1}=\"\\if \\1 \\warning test \\1 failed 	\\endif\"\nENABLED_SECTIONS = ");
#else
#define CREATE_TEST checkygenfl=NULL;
#endif

#define START_TEST if(checkygenfl) {if(!find_checkygennode(checkygenfl, __LINE__, __FILE__)) { if(!push_checkygennode(checkygenfl, __LINE__, __FILE__)) ERROR; int testcounter = 0;

#define TEST(a) if(checkygenfl){{testcounter++; if(!(a)) {printf("\n\x1b[41m" "\t%d. test of \"%s(...)\" failed    in file %s, line %d\x1B[0m\n",testcounter, __func__, __FILE__, __LINE__);fflush(stdout);fprintf(checkygenfp," %s%d ",__func__ ,testcounter);}else {printf("\n\x1B[44m" "\t%d. test of \"%s(...)\" succeeded in file %s, line %d\x1b[0m\n",testcounter, __func__, __FILE__, __LINE__ );fflush(stdout);};};};

#define STOP_TEST if(errno!=EXIT_SUCCESS) return errno;};};

#define REMOVE_TEST if(checkygenfl){ remove_checkygenlist(checkygenfl);fclose(checkygenfp);};

/* Some macros for poor debugging: */

#define PINT(i) {printf("( "#i ") == %d\n",i);}
#define PFLOAT(x) {printf("( "#x ") == %f\n",x);}
#define NOW {printf("\x1b[43m %d %s\x1b[0m\n", __LINE__, __FILE__);fflush(stdout);}
#define IN  {printf("\x1b[43m" "IN " "\x1b[0m\n");fflush(stdout);}
#define OUT {printf("\x1b[43m" "OUT" "\x1b[0m\n");fflush(stdout);}

#define ERROR {printf("\x1b[43m\n\t\t%d %s: %s\x1b[0m\n", __LINE__,  __FILE__,strerror(errno));}

/* "otherwise goto label x": a macro, useful for goto-chains.
e.g. see: https://resources.sei.cmu.edu/asset_files/Presentation/2016_017_101_484207.pdf */

#define OGL(x) {if(x==NULL)	{ERROR;goto x ## _label;};}

#endif
