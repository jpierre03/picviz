CC=gcc
LIBS=`pkg-config --libs picviz` -lev
CFLAGS=`pkg-config --cflags picviz` -ggdb

all: pcvd

pcvd: Makefile pcvd.c
	$(CC) pcvd.c -o pcvd $(LIBS) $(CFLAGS)

