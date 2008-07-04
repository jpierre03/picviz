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

#include <pcimage.h>
#include <linuxlist.h>

#include "axis.h"
#include "line.h"

/**
 * \ingroup PicvizMain
 * @{
 */

/** \file axis.c
 * \brief Create and manipulate axes
 */

static unsigned int id = 0;

struct axis_properties_t *picviz_axis_properties_new(void)
{
        struct axis_properties_t *props;

        props = malloc(sizeof(*props));
        if ( ! props ) {
                fprintf(stderr, "Cannot create axis properties: memory exhausted.\n");
                return NULL;
        }

        //props->label = strdup("");
        props->label = "";
        props->color = ""; /* black */

        return props;
}

struct axis_t *picviz_axis_new(void)
{
        struct axis_t *axis = NULL;

        axis = malloc(sizeof(*axis));
        if ( ! axis ) {
                fprintf(stderr, "Cannot initialize axis: memory exhausted.\n");
                return NULL;
        }
        INIT_LLIST_HEAD(&axis->list);
        axis->id = id++;
        axis->props = picviz_axis_properties_new();
        axis->type = DATATYPE_EMPTY;
        axis->xpos = 0;
        axis->ymin = 0; /* FIXME: that must be auto-adaptative */
        axis->ymax = 0;

        return axis;
}

void picviz_axis_destroy(struct pcimage_t *image)
{

        struct llist_head *lcounter, *tmplist;
        struct axis_t *axistmp;

        if (!image->axes) return;

        llist_for_each_safe(lcounter, tmplist, &image->axes->list) {
                axistmp = llist_entry(lcounter, struct axis_t, list);
                llist_del(lcounter);
                free(axistmp->props);
                free(axistmp);
        }

}

struct axis_t *picviz_axis_get(struct pcimage_t *i, unsigned int id)
{
        struct axis_t *a;

        llist_for_each_entry(a, &i->axes->list, list) {
                if (a->id == id) return a;
        }
}

void picviz_axis_props_set(struct axis_t *axis, struct axis_properties_t *props)
{
        axis->props = props;
}

void picviz_axis_set_type(struct axis_t *axis, enum datatype_t type)
{
        axis->type = type;
}

void picviz_axis_set_type_from_string(struct axis_t *axis, char *string)
{
        if (!strcmp(string, "timeline")) {
                axis->type = DATATYPE_TIMELINE;
                return;
        }
        if (!strcmp(string, "integer")) {
                axis->type = DATATYPE_INTEGER;
                return;
        }
        if (!strcmp(string, "string")) {
                axis->type = DATATYPE_STRING;
                return;
        }
        if (!strcmp(string, "float")) {
                axis->type = DATATYPE_FLOAT;
                return;
        }
        if (!strcmp(string, "short")) {
                axis->type = DATATYPE_SHORT;
                return;
        }
        if (!strcmp(string, "ipv4")) {
                axis->type = DATATYPE_IPV4;
                return;
        }
        if (!strcmp(string, "char")) {
                axis->type = DATATYPE_CHAR;
                return;
        }
        if (!strcmp(string, "gold")) {
                axis->type = DATATYPE_GOLD;
                return;
        }
        if (!strcmp(string, "epoch")) {
                axis->type = DATATYPE_EPOCH;
                return;
        }

        axis->type = DATATYPE_EMPTY;
}

#if 0
void picviz_axis_prop_set_label(struct axis_t *axis, char *label)
{
        axis->label = label;
}
#endif

struct axisplot_t *picviz_axisplot_new(void)
{
        struct axisplot_t *axisplot;

        axisplot = malloc(sizeof(*axisplot));
        if ( ! axisplot ) {
                fprintf(stderr, "Cannot initalize axisplot: memory exhaustred.\n");
                return NULL;
        }

        INIT_LLIST_HEAD(&axisplot->list);
        axisplot->strval  = NULL;
        axisplot->y       = 0;
        axisplot->axis_id = 0;

        return axisplot;
}

