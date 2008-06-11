YACC=bison
LEX=flex
CC=gcc
CFLAGS=-D_UNIT_TEST_ -g -I../ -I../include -DDEBUGPROPERTY -DDEBUGSR
LIBS=-lfl -ly -lpicviz

all: parser

parser: lexer.l parser.y
	$(YACC) -d parser.y
	$(LEX) lexer.l
	$(CC) lex.yy.c parser.tab.c -o parser $(CFLAGS) $(LIBS)

clean:
	rm -f parser
	rm -f lex.yy.c
	rm -f parser.tab.c
	rm -f parser.tab.h

