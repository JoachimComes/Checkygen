#/***************************************************************************
# *   Copyright (C) 2021 by Joachim Comes                                   *
# *   jcomes@prima-philosophia.org                                          *
# *                                                                         *
# *   This program is free software: you can redistribute it and/or modify  *
# *   it under the terms of the GNU Affero General Public License as        *
# *   published by the Free Software Foundation, either version 3 of the    *
# *   License, or (at your option) any later version.                       *
# *			                                                               *
# *   This program is distributed in the hope that it will be useful,       *
# *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
# *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
# *   GNU Affero General Public License for more details.                   *
# *                                                                         *
# *   You should have received a copy of the GNU General Public License     *
# *   along with this program; if not, write to the                         *
# *   Free Software Foundation, Inc.,                                       *
# *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
# ***************************************************************************/

#									Makefile

DEBUGFLAG = 1

CFLAGS    = 
 
LDFLAGS   = -lblasfeo -lhpipm -lbayesopt -lblas -lgsl -lm

CC        = gcc

# DO NOT EDIT BELOW THIS LINE ################################################

DBG_CFLAGS  = -pedantic -Wall -W -Wmissing-prototypes -Wstrict-prototypes -Wconversion -Wshadow -Wpointer-arith
DBG_CFLAGS += -Wcast-qual -Wcast-align -Wwrite-strings -Wnested-externs -Wmissing-declarations -Winline -fshort-enums -fno-common
DBG_CFLAGS += -Dinline= -ggdb3 -O0 -fprofile-arcs -ftest-coverage 
DBG_CFLAGS += -fstack-protector-strong -fprofile-arcs -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment 
DBG_CFLAGS += -v -pg -g -DLONG -DDEBUG -DCHECKYGEN

DBG_LDFLAGS = -pg -g -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment

ifeq (${DEBUGFLAG},1)

CFLAGS  += ${DBG_CFLAGS}

LDFLAGS += ${DBG_LDFLAGS}

else

CFLAGS  += -O3 -DHAVE_INLINE -DGSL_RANGE_CHECK_OFF -DNDEBUG -DNCHECKYGEN

endif

SRC := $(wildcard *.c)
OBJ := $(SRC:.c=.o)

program: $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LDFLAGS)

%.d: %.c
	$(CC) -MM -MT '$(@:.d=.o)' $< -MF $@

-include $(SRC:.c=.d)

%.o: %.c
	if [ -f scan.l  ]; then flex -i scan.l ; fi
	if [ -f parse.y ]; then bison -ydtv parse.y; fi
	$(CC) $(CFLAGS) -c $< -o $@

check:
	
	reset

	@echo "\n\n\n\t\t\t*** C P P C H E C K ***\n\n\n"
	cppcheck -I/usr/local/include/ --enable=all ./
	
#	@echo "\n\n\n\t\t\t*** V A L G R I N D ***\n\n\n"
#	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -v ./a.out
#   sanitizer problems

	@echo "\n\n\n\t\t\t*** G C O V ***\n\n\n"
	gcov -b *.c
	./a.out
	
	@echo "\n\n\n\t\t\t*** G P R O F ***\n\n\n"
	gprof -b a.out gmon.out

	./checkygen.sh

clean:
	astyle --style=allman --indent=tab --break-blocks --pad-oper --pad-comma --pad-paren --pad-header --align-pointer=middle --max-code-length=200 --break-after-logical -v $(PWD)/*.c $(PWD)/*.h
	rm -fr a.out y.*  *.o *.d *.gcda *.gcno *.gcov core.* gmon.out lex.yy.c *.tab.* *.depend *.plist *.orig tags *.swp 	Checkyfile Doxyfile html latex  
	touch *.*
	reset

