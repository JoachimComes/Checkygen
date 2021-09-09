#!/bin/bash
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

#								checkygen.sh

printf "\n\n\n\t\t\t*** D O X Y G E N ***\n"
if !(test -f Doxyfile);
	then doxygen -g;
fi;
cp Doxyfile Doxyfile0
cat Doxyfile Checkyfile > Doxyfile
doxygen 
mv Doxyfile0 Doxyfile
