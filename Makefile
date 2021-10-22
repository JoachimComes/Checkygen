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
CFLAGS    = -I./hpipm/include     -I./blasfeo/include
 
LDFLAGS   = -L./hpipm/lib -lhpipm -L./blasfeo/lib -lblasfeo -lgsl -lcblas -lopenblas -lm

# DO NOT EDIT BELOW THIS LINE ################################################

CC        = gcc

#   GCC warning options for numerical programs
#   https://www.gnu.org/software/gsl/doc/html/debug.html#gcc-warning-options-for-numerical-programs
#   but changing "-ansi" to "-std=gnu99"
DBG_CFLAGS  = -std=gnu99 -pedantic -Werror -Wall -W -Wmissing-prototypes -Wstrict-prototypes -Wconversion -Wshadow -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wnested-externs -fshort-enums -fno-common -Dinline= -g -O2
#   gcov
DBG_CFLAGS += -fprofile-arcs -ftest-coverage
#   gprof
DBG_CFLAGS += -pg
DBG_LFLAGS  = -pg
#   sanitizer
DBG_CFLAGS += -fsanitize=address -fsanitize=undefined -fno-sanitize-recover=all -fsanitize=float-divide-by-zero -fsanitize=float-cast-overflow -fno-sanitize=null -fno-sanitize=alignment
#   analyzer
DBG_CFLAGS +=-fanalyzer
#   switches
DBG_CFLAGS += -DDEBUG -DCHECKYGEN

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
	./a.out
	@echo "\n\n\n\t\t\t*** G C O V ***\n\n\n"
	gcov -b *.c	
	@echo "\n\n\n\t\t\t*** G P R O F ***\n\n\n"
	gprof -b 
	@echo "\n\n\n\t\t\t*** D O X O G Y E N ***\n\n\n"
	./checkygen.sh


clean:
	astyle --style=allman --indent=tab --break-blocks --pad-oper --pad-comma --pad-paren --pad-header --align-pointer=middle --max-code-length=200 --break-after-logical -v $(PWD)/*.c $(PWD)/*.h
	rm -fr a.out y.*  *.o *.d *.gcda *.gcno *.gcov core.* gmon.out lex.yy.c *.tab.* *.depend *.plist *.orig tags *.swp *.swo Checkyfile Doxyfile html latex  
	touch *.*
	reset

