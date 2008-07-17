%{
#include <stdio.h>
#include <string.h>
#include <picviz.h>

int axis_position;

extern int yylex(void);
extern void yylex_init(void);
extern void yylex_destroy(void);
extern void yyerror(char *);
extern void *yy_scan_string(const char *);
extern void yy_delete_buffer(void *);

typedef enum section_t {
        EMPTY,
        HEADER,
        ENGINE,
        AXES,
        DATA
} section_t;

static section_t section_state = EMPTY;
int close_section_check = 0;
struct axis_t *axis;
float lines_values[PICVIZ_MAX_AXES]; /* store positions */
int max_axes = 0; /* to know if we should clean lines_values */
struct pcimage_t *image;
struct line_t *line;
int i = 0;
char *line_color;
char *axis_label = "";

/* I know this is ugly,
 * I'll get back to it latter
 */
#define FILE_MODE 0
#define LINE_MODE 1
char FILE_OR_LINE = FILE_MODE;

#define YY_ABORT return -1;
#define YYERROR_VERBOSE

%}

%token  TOK_SEMICOLON
%token  TOK_COMMA

%token  TOK_EQUAL
%token  <string> TOK_STRING
%token  <string> TOK_DQSTRING
%token  <string> TOK_WORD
%token  <string> TOK_DATATYPE

%token  <string> TOK_SECTION
%token  TOK_OPEN_SECTION
%token  TOK_CLOSE_SECTION

%token  <string> TOK_PROPERTY
%token  TOK_OPEN_PROP
%token  TOK_CLOSE_PROP

%union {
        char *string;
        int   number;
}

%type <string> property
%type <string> properties
%type <string> value
%type <string> dataval

%start pcv

%%

pcv:    /* empty */
        | pcv section_new
        | pcv key_value_data
	| pcv type_var TOK_SEMICOLON
        | pcv section_end
        ;

section_new:    TOK_SECTION TOK_OPEN_SECTION
                {
#ifdef DEBUGSR /* Debug shifts-reduces*/
        printf("==> section_new:    TOK_SECTION(%s) TOK_OPEN_SECTION\n", $1);
#endif /* DEBUGSR */

                        if (close_section_check) {
                                yyerror("Opening new section, but the latest was not closed");
                                YY_ABORT;
                        }

                        if (!strncmp($1, "header", 6)) {
                                section_state = HEADER;
                        } else if (!strncmp($1, "engine", 6)) {
                                section_state = ENGINE;
                        } else if (!strncmp($1, "axes", 4)) {
                                section_state = AXES;
                        } else if (!strncmp($1, "data", 4)) {
                                section_state = DATA;
                        }

                        close_section_check++;
#ifdef DEBUG
                        printf("New section: %s\n", $1);
#endif
                        free($1);

#ifdef DEBUGSR
        printf("<== section_new:    TOK_SECTION TOK_OPEN_SECTION\n");
#endif /* DEBUGSR */
                }
                ;

property:
		TOK_PROPERTY TOK_EQUAL TOK_DQSTRING
                {
#ifdef DEBUGSR
        printf("==> property:       TOK_PROPERTY(%s) TOK_EQUAL TOK_DQSTRING(%s)\n", $1, $3);
#endif /* DEBUGSR */
                        //printf("prop=%s, val=%s\n", $1, $3);
                        switch (section_state) {
                                case DATA:
                                       if (!strcmp("color",$1)) {
                                                line_color = strdup($3);
                                                //picviz_line_prop_color_set(line, $3);
                                        }
                                        // Add line property
                                        break;
                                case AXES:
                                        if (!strcmp("label",$1))
                                        {
                                                axis_label = strdup($3);
                                                engine.__axis_label_exists = 1;
                                        }
                                        break;
                        }

                        free($1);
                        free($3);
#ifdef DEBUGSR
        printf("<== property:       TOK_PROPERTY TOK_EQUAL TOK_DQSTRING\n");
#endif /* DEBUGSR */
                }
                ;

properties:
	property
	{
		$$ = $1;
	}
	|
	property TOK_COMMA properties
	{
		$$ = $1;
	}

type_var:	TOK_DATATYPE TOK_WORD
		{
#ifdef DEBUGSR
        printf("==> type_var:	TOK_DATATYPE(%s) TOK_WORD(%s)\n", $1, $2);
#endif /* DEBUGSR */
                        axis = picviz_axis_new();
                        picviz_axis_set_type_from_string(axis, $1);
                        picviz_image_axis_append(image, axis);

                        max_axes++;

                        free($1);
                        free($2);
#if 0
                        axes[max_axes] = picviz_axis_new();
                        picviz_image_axis_append(image, axes[max_axes]);
#endif
#ifdef DEBUG
			printf("data with no props\n");
#endif
#ifdef DEBUGSR
        printf("<== type_var:	TOK_DATATYPE TOK_WORD\n");
#endif /* DEBUGSR */
		}
		| TOK_DATATYPE TOK_WORD TOK_OPEN_PROP properties TOK_CLOSE_PROP
		{
#ifdef DEBUGSR
        printf("==> type_var:    TOK_DATATYPE(%s) TOK_WORD(%s) TOK_OPEN_PROP property TOK_CLOSE_PROP\n", $1, $2);
#endif /* DEBUGSR */
                        axis = picviz_axis_new();
                        picviz_axis_set_type_from_string(axis, $1);
                        axis->props->label = axis_label;
                        axis_label = "";
                        picviz_image_axis_append(image, axis);

                        max_axes++;

                        free($1);
                        free($2);
#ifdef DEBUG
			printf("data with props\n");
#endif
#ifdef DEBUGSR
        printf("<== type_var:    TOK_DATATYPE TOK_WORD TOK_OPEN_PROP property TOK_CLOSE_PROP\n");
#endif /* DEBUGSR */
                       // axis = picviz_axis_new();

                       // free($1);
                       // free($2);
		}
                ;

/* l="foo",p="bar" */
value: TOK_WORD TOK_EQUAL TOK_DQSTRING
        {
#ifdef DEBUGSR
        printf("==> dataval: TOK_WORD(%s) TOK_EQUAL TOK_DQSTRING(%s)\n", $1, $3);
#endif /* DEBUGSR */
                struct axisplot_t *axisplot;

                if ( section_state == DATA ) {
                        if ( ! axis_position ) {
                                line = picviz_line_new();
                        }

                        axisplot = picviz_axisplot_new();
                        //axisplot->strval = strdup($3);
                        axisplot->strval = strdup($3);
                        /* We first dump data into the structure, we render latter */
                        //axisplot->y = picviz_line_value_get_from_string($3);
                        axisplot->axis_id = axis_position + 1;
                        picviz_line_axisplot_append(line, axisplot);

                        //lines_values[axis_position] = picviz_line_value_get_from_string($3);
#ifdef DEBUGDATA
                        printf("[%d]variable=%s,value=%s\n", axis_position, $1, $3);
#endif
                        //printf("ma=%d, position=%d\n",max_axes, axis_position);
                        axis_position++;

                } else if ( section_state == ENGINE ) {
                        if ( ! strcmp($1, "axis_default_space") ) {
                                engine.axis_default_space = atoi($3);
                        }
                }
	//	else if ( section_state == HEADER ) {
	//		if ( ! strcmp($1, "bgcolor") ) {
	//			image->bg_color = strdup($3);
	//		}
	//	}

                free($3);
                free($1);
#ifdef DEBUGSR
        printf("<== dataval: TOK_WORD TOK_EQUAL TOK_DQSTRING\n");
#endif /* DEBUGSR */

        }
	;

dataval: value
	{
		$$ = $1;
	}
        |
        value TOK_COMMA dataval
	{
		$$ = $1;
	}
        ;

key_value_data: dataval TOK_OPEN_PROP property TOK_CLOSE_PROP TOK_SEMICOLON
                {
#ifdef DEBUGSR
        printf("==> key_value_data: dataval TOK_OPEN_PROP property TOK_CLOSE_PROP TOK_SEMICOLON\n");
#endif /* DEBUGSR */
                        if ( section_state == DATA ) {
                                picviz_line_prop_color_set(line, line_color);
                                free(line_color);
				if (FILE_OR_LINE == FILE_MODE) {
                                	picviz_image_line_append(image, line);
				}
                        }
#if 0
#ifdef DEBUGAXES
                        printf("1=%f,2=%f,3=%f\n", lines_values[0], lines_values[1], lines_values[2]);
#endif
                        for (i = 0; i < (max_axes - 1); i++) {
                                line = picviz_line_init();
                                picviz_line_prop_color_set(line, line_color);
                                picviz_line_src_dst_set(line, lines_values[i], lines_values[i+1]);
                                picviz_axis_line_append(axes[i], line);
                        }
                        line = picviz_line_init();
                        picviz_line_prop_color_set(line, line_color);
                        picviz_line_src_dst_set(line, lines_values[i], -1);
                        picviz_axis_line_append(axes[i], line);
                        line_color = "#000000";
                //        printf("Finalize\n");
#endif
#ifdef DEBUGSR
        printf("<== key_value_data: dataval TOK_OPEN_PROP property TOK_CLOSE_PROP TOK_SEMICOLON\n");
#endif /* DEBUGSR */
                }
                |
                dataval TOK_SEMICOLON
                {
#ifdef DEBUGSR
        printf("==> dataval TOK_SEMICOLON\n");
#endif /* DEBUGSR */


                        if ( section_state == DATA ) {
				if (FILE_OR_LINE == FILE_MODE) {
                                	picviz_image_line_append(image, line);
				}
                        }
                        //for (i=0; i<(max_axes-1);i++) {
                        //}
#if 0
                        if (axes[i]) {
                                for (i = 0; i < (max_axes - 1); i++) {
                                        line = picviz_line_init();
                                        picviz_line_src_dst_set(line, lines_values[i], lines_values[i+1]);
                                        picviz_axis_line_append(axes[i], line);
                                }
                                line = picviz_line_init();
                                picviz_line_src_dst_set(line, lines_values[i], -1);
                                picviz_axis_line_append(axes[i], line);
                        }
#endif
#ifdef DEBUGSR
        printf("<== dataval TOK_SEMICOLON\n");
#endif /* DEBUGSR */
                }
                ;

section_end:    TOK_CLOSE_SECTION
                {
                        close_section_check--;
                }
                ;

%%

void yyerror(char *str)
{
	fprintf(stderr, "YYERROR:%s\n", str);
}

struct pcimage_t *pcv_parse(char *filename)
{
        extern FILE *yyin;

        axis_position = 0;

        image = picviz_image_new();

        yyin = fopen(filename,"r");
        if ( ! yyin ) {
                fprintf(stderr, "Cannot open file '%s'\n", filename);
                return NULL;
        }
        line_color = strdup("#000000");
        yyparse();

        picviz_render_image(image);

        return image;
        //image_to_svg(image);
        //picviz_image_debug_printall(image);
}

struct line_t *picviz_parse_line(char *string)
{
	void *state;
	int ret;

//	memset(line, 0, sizeof(struct line_t *));
	FILE_OR_LINE = LINE_MODE;

	section_state = DATA;
	state = yy_scan_string(string);
	ret = yyparse();
	yy_delete_buffer(state);

	return line;
}

#ifdef _UNIT_TEST_
/* gcc config-parser.lex.c config-parser.yacc.c -o config-parser -D_UNIT_TEST_ -ly -lfl */
int main(void)
{

        axis_position = 0;

        pcv_parse("test.pcv");

        //printf("Parsing finished\n");
        picviz_image_debug_printall(image);

        return 0;
}
#endif

