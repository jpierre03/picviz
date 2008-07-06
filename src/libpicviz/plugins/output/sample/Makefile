#PICVIZ_LIB_DIR = $(DESTDIR)/lib/security
PICVIZ_LIB_DIR = .
CC = gcc
LD = ld
INSTALL = /usr/bin/install
CFLAGS = -fPIC -O2 -c -g -Wall -Wformat-security -fno-strict-aliasing -I../../../include
LDFLAGS = -x --shared
PICVIZLIB = -lpicviz
CPPFLAGS =

all: libsvg.so

libsvg.so: libsvg.o
	$(LD) $(LDFLAGS) -o libsvg.so libsvg.o $(PICVIZLIB)

libsvg.o: libsvg.c
	$(CC) $(CFLAGS) libsvg.c

install: libsvg.so
	$(INSTALL) -m 0755 -d $(PICVIZ_LIB_DIR)
	$(INSTALL) -m 0644 libsvg.so $(LIBVIZ_LIB_DIR)

clean:
	rm -f libsvg.o libsvg.so

