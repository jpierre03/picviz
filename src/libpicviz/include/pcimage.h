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

#include "linuxlist.h"
#include "engine.h"

#ifndef _PCIMAGE_H_
#define _PCIMAGE_H_

typedef enum datatype_t {
        DATATYPE_EMPTY,
        DATATYPE_INTEGER,
        DATATYPE_FLOAT,
        DATATYPE_STRING,
        DATATYPE_TIMELINE,
        DATATYPE_SHORT,
        DATATYPE_IPV4,
        DATATYPE_GOLD,
        DATATYPE_CHAR
} datatype_t;

typedef struct axis_properties_t {
        char *label;
        char *color;
} axis_properties_t;

typedef struct line_properties_t {
        char *label;
        char *color;
} line_properties_t;

typedef struct axisplot_t {
        struct llist_head list;
        char *strval; /* This is the string value of the ysource, to put (optionally) in the graph */
        float y;         /* where does the line goes on this axis */
        unsigned int axis_id; /* id of the axis we positionate the line to */
} axisplot_t;

typedef struct line_t {
        struct llist_head list;
        unsigned int id;
        struct axisplot_t *axisplot;
        struct line_properties_t *props;
} line_t;

typedef struct axis_t {
        struct llist_head list;
        unsigned int id;
        struct axis_properties_t *props;
        datatype_t type;
        unsigned int   xpos;     /* pos of the axis */
        float ymin; /* Where we start (top): Not max line, max of what we see */
        float ymax; /* Where we end (botton): Not min line */
} axis_t;

typedef struct pcimage_t {
        unsigned int width;
        unsigned int height;
        unsigned int header_height;

        enum position_t zero_pos; /* where the zero value is on the axes */

        struct axis_t *axes;
        struct line_t *lines;

} pcimage_t;

#endif /* _PCIMAGE_H_ */

