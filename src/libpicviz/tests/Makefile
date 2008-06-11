CC=gcc
CFLAGS=-g -I../ -I../include -I../parser/
LIBS=-lpicviz -lfl -ly

all: tests

tests: test1.c test2.c test3.c test4.c test-colors.c
	$(CC) test1.c -o test1 $(CFLAGS) $(LIBS)
	$(CC) test2.c -o test2 $(CFLAGS) $(LIBS)
	$(CC) test3.c -o test3 $(CFLAGS) $(LIBS)
	$(CC) test4.c -o test4 $(CFLAGS) $(LIBS)
	$(CC) test-colors.c -o test-colors $(CFLAGS) $(LIBS)

clean:
	rm -f test1
	rm -f test2
	rm -f test3
	rm -f test4
	rm -f *.svg

