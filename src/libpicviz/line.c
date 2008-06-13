/*
 * Picviz - Parallel coordinates ploter
 * Copyright (C) 2008 Sebastien Tricaud <toady@gscore.org>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <picviz.h>

#include <color.h>

#include "defaults.h"
#include "axis.h"
#include "line.h"

static PcvID id = 0;

struct line_properties_t *picviz_line_properties_new(void)
{
        struct line_properties_t *props;

        props = malloc(sizeof(*props));
        if ( ! props ) {
                fprintf(stderr, "Cannot create line properties: memory exhausted.\n");
                return NULL;
        }

        props->label = "";
        //props->color = strdup("#000000"); /* black */
        props->color = "#000000"; /* black */

        return props;
}

struct line_t *picviz_line_new(void)
{
        struct line_t *line;

        line = malloc(sizeof(*line));
        if ( ! line ) {
                fprintf(stderr, "Cannot initialize line: memory exhausted.\n");
                return NULL;
        }
        INIT_LLIST_HEAD(&line->list);
        line->id = id++;
        line->props = picviz_line_properties_new();
        line->axisplot = picviz_axisplot_new();

        return line;
}

void picviz_line_axisplot_append(struct line_t *line, struct axisplot_t *axisplot)
{
        llist_add_tail(&axisplot->list, &line->axisplot->list);
}


void picviz_line_free(struct line_t *l)
{
        free(l->props);
        free(l);

}

void picviz_line_prop_color_set(struct line_t *line, PcvString color)
{
        line->props->color = picviz_color_named_to_hexstr(color);
}

PcvString picviz_line_prop_color_get(struct line_t *line)
{
        return line->props->color;
}


PcvHeight picviz_line_max_get(struct line_t *line, PcvID axis_id)
{
        struct axis_t *a;
        struct line_t *l;
        struct axisplot_t *axisplot;
        char init = 0;
        PcvHeight max = 0;

        llist_for_each_entry(l, &line->list, list) {
                llist_for_each_entry(axisplot, &l->axisplot->list, list) {
                        if (axis_id == axisplot->axis_id) {
                                if ( ! init ) {
                                        init = 1;
                                        max = axisplot->y;
                                }

                                if ( axisplot->y > max ) max = axisplot->y;
                        }
                }
        }

        return max;
}

PcvHeight picviz_line_max_pertype_get(struct pcimage_t *image, datatype_t type)
{
        struct line_t *line;
        struct axisplot_t *axisplot;
        int i;
        int nb_types = sizeof(datatype_t);
        char init[nb_types];
        PcvHeight max[nb_types];

        for ( i = 0; i <= nb_types; i++) {
                init[i] = 0;
        }

        llist_for_each_entry(line, &image->lines->list, list) {
                llist_for_each_entry(axisplot, &line->axisplot->list, list) {
                        struct axis_t *axis = (struct axis_t *)picviz_axis_get(image, axisplot->axis_id);

                        if (axis->type == type) {
                                if ( ! init[type] ) {
                                        init[type] = 1;
                                        max[type] = axisplot->y;
                                }

                                if ( axisplot->y > max[type] ) max[type] = axisplot->y;

                        }
                }
        }

        return max[type];
}

