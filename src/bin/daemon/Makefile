CC=gcc
LIBS=`pkg-config --libs picviz`
CFLAGS=`pkg-config --cflags picviz`

all: pcvd

pcvd: pcvd.c
	$(CC) pcvd.c -o pcvd $(LIBS) $(CFLAGS)

