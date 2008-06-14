
/*
 * Written by Sebastien Tricaud (c) 2008
 * Part of the PicViz project
 */


%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "parser.h"

extern int axis_position;

static char *escape_str(char *str)
{
        size_t w = 0, i = 0;
        int escape_next = 0;

        for ( i = 1; str[i]; i++ ) {

                if ( ! escape_next && str[i] == '\\' ) {
                        escape_next = 1;
                        continue;
                }

                str[w++] = str[i];
                escape_next = 0;
        }

        str[w - 1] = '\0';
        return str;
}


%}
%option noyywrap

SECTION		(header|engine|axes|data)
OPEN_SECTION    \{
CLOSE_SECTION   \}
DATATYPE	(timeline|integer|float|string|short|ipv4|gold|char)
OPEN_PROP	\[
CLOSE_PROP	\]
PROPERTY        (label|color)
SQSTRING	\'([^\\\']|\\.)*\'
DQSTRING	\"([^\\\"]|\\.)*\"
STRING		(\"|\')([^\\(\"|\')]|\\.)*(\"|\')
COMMENT		^#.*\n
WORD		([a-zA-Z0-9_\-]+(\(\-?[0-9\*]+\))?\.?)+
SEMICOLON	\;
COMMA		\,
EQUAL		\=
VOID		[ \t]+
NEWLINE         \n

%%

{PROPERTY}      { yylval.string = strdup(yytext);
                  return TOK_PROPERTY; }
{OPEN_PROP}     { return TOK_OPEN_PROP; }
{CLOSE_PROP}     { return TOK_CLOSE_PROP; }

{SEMICOLON}	{ return TOK_SEMICOLON; }
{COMMA}		{ return TOK_COMMA; }

{SECTION}	{	yylval.string = strdup(yytext);
			return TOK_SECTION;
		}
{OPEN_SECTION}  {       return TOK_OPEN_SECTION; }
{CLOSE_SECTION}  {       return TOK_CLOSE_SECTION; }

{DATATYPE}	{	yylval.string = strdup(yytext);
			return TOK_DATATYPE;
		}

{DQSTRING}      {
                        yylval.string = strdup(escape_str(yytext));
                        return TOK_DQSTRING;
                }

{WORD}		{	yylval.string = strdup(yytext);
			return TOK_WORD;
		}

{EQUAL}		{	return TOK_EQUAL; }

{STRING}	{
			yylval.string = strdup(escape_str(yytext));
			return TOK_WORD;
		}


{COMMENT}	{
			/* We don't care */
		}

{VOID}		{
			/* We don't care */
		}

{NEWLINE}       {
                        axis_position = 0;
                }

%%


