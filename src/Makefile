##########################################################################
# Makefile
#
# This software is a devLib extension to wiringPi <http://wiringpi.com/>
# and enables it to read an bme180 chip
# 
#
# Copyright (c) 2020 Wade Ryan
#
# If you have questions or improvements email me at
# wryan67@gmail.com
#
# This software is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published
# by the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# The given code is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU Lesser General Public License for more details.
#
# You can view the contents of the licence at <http://www.gnu.org/licenses/>.
##########################################################################


DYN_VERS_MAJ=1
DYN_VERS_MIN=0

VERSION=$(DYN_VERS_MAJ).$(DYN_VERS_MIN)
DESTDIR=/usr
PREFIX=/local

STATIC=libwiringPiBME280rpi.a
DYNAMIC=libwiringPiBME280rpi.so.$(VERSION)

# Use this line for debugging:
# DEBUG	= -g -O0 -rdynamic
# Production
DEBUG	= -O2
CC	= gcc
INCLUDE	= -I.
CFLAGS	= $(DEBUG) -Wformat=2 -Wall $(INCLUDE) -Winline -pipe -fPIC

LIBS    =

###############################################################################

SRC	= bme280rpi.c

OBJ	=	$(SRC:.c=.o)

all:		$(DYNAMIC)

static:		$(STATIC)

$(STATIC):	$(OBJ)
	@echo "[Link (Static)]"
	@ar rcs $(STATIC) $(OBJ)
	@ranlib $(STATIC)
#	@size   $(STATIC)

$(DYNAMIC):	$(OBJ)
	@echo "[Link (Dynamic)]"
	@$(CC) -shared -Wl,-soname,libwiringPiBME280rpi.so -o libwiringPiBME280rpi.so.$(VERSION) -lpthread $(OBJ)

.c.o:
	@echo [Compile] $<
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	@echo "[Clean]"
	@rm -f $(OBJ) $(OBJ_I2C) *~ core tags Makefile.bak libwiringPiBME280rpi.*

tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)


install-headers:
	@echo "[Install Headers]"
	@install -m 0755 -d			$(DESTDIR)$(PREFIX)/include
	@install -m 0644 bme280rpi.h		$(DESTDIR)$(PREFIX)/include

install:	$(DYNAMIC) install-headers
	@echo "[Install Dynamic Lib]"
	@install -m 0755 -d						$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 libwiringPiBME280rpi.so.$(VERSION)			$(DESTDIR)$(PREFIX)/lib/libwiringPiBME280rpi.so.$(VERSION)
	@ln -sf $(DESTDIR)$(PREFIX)/lib/libwiringPiBME280rpi.so.$(VERSION)	$(DESTDIR)/lib/libwiringPiBME280rpi.so
	@ldconfig

install-static:	$(STATIC) install-headers
	@echo "[Install Static Lib]"
	@install -m 0755 -d			$(DESTDIR)$(PREFIX)/lib
	@install -m 0755 libwiringPiBME280rpi.a	$(DESTDIR)$(PREFIX)/lib

uninstall:
	@echo "[UnInstall]"
	@rm -f $(DESTDIR)$(PREFIX)/include/bme280rpi.h
	@rm -f $(DESTDIR)$(PREFIX)/lib/libwiringPiBME280rpi.*
	@ldconfig


depend:
	makedepend -Y $(SRC)


libwiringPiBME280rpi.o: bme280rpi.h
