CC=gcc
CFLAGS=-g -I../ -I../libpicviz/include -I../libpicviz/parser/
LIBS=-lpicviz

all: picviz

picviz: picviz.c
	$(CC) picviz.c -o picviz $(CFLAGS) $(LIBS)

clean:
	rm -f picviz

