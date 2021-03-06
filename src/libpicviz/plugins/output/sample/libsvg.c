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
#include <string.h>
#include <stdlib.h>

#include <debug.h>
#include <linuxlist.h>
#include <plugins.h>

#define FONT_SIZE_PER_CHAR 4

int get_x_from_string(int axis_x, char *str)
{
        int x;

        x = (strlen(str) * FONT_SIZE_PER_CHAR) / 2;

        return axis_x - x;
}

void output(pcimage_t *i)
{
        struct axis_t *a;
        struct line_t *l;
        struct axisplot_t *axisplot;

        PcvWidth  last_x = -1;
        PcvHeight last_y = -1;

        printf("<?xml version=\"1.0\" standalone=\"no\"?>\n");
        printf("<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" \"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n");
        printf("<svg width=\"%d\" height=\"%d\" version=\"1.1\" xmlns=\"http://www.w3.org/2000/svg\">\n",
                i->width, i->height);
        printf("  <desc>Picviz image</desc>\n\n");

        printf("/* Axes */\n");

        llist_for_each_entry(a, &i->axes->list, list) {
                printf("<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"0.1\"/>\n",
                        a->xpos, i->header_height, a->xpos, i->height);
                printf("<text style=\"fill:black;font-size:8px;font-family:Courier 10 Pitch\" x=\"%d\" y=\"10\">%s</text>\n", get_x_from_string(a->xpos, a->props->label), a->props->label);
                printf("<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"0.1\"/>\n", a->xpos + (engine.axis_default_space/2), 0, a->xpos + (engine.axis_default_space/2), i->header_height);
        }

        printf("<line x1=\"0\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"black\" stroke-width=\"0.1\"/>\n", i->header_height, i->width, i->header_height);
        printf("\n/* Lines */\n");

        llist_for_each_entry(l, &i->lines->list, list) {
                llist_for_each_entry(axisplot, &l->axisplot->list, list) {
                        struct axis_t *axis = (struct axis_t *)picviz_axis_get(i, axisplot->axis_id);

                        if (axis->id == 1) {
                                last_y = axisplot->y + i->header_height;
                                last_x = axis->xpos;
                        } else {
                                printf("<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" ",
					last_x, last_y, axis->xpos, axisplot->y + i->header_height);
				printf("stroke=\"%s\" stroke-width=\"0.1\"/>\n",
                                        l->props->color);
                                last_x = axis->xpos;
                                last_y = axisplot->y + i->header_height;

                        }
                        if (engine.display_raw_data) {
                                printf("<text style=\"fill:black;font-size:5px;font-family:Courier 10 Pitch\" x=\"%d\" y=\"%d\">%s</text>\n", axis->xpos, axisplot->y + i->header_height, axisplot->strval);
                        }
                }
        }

        printf("</svg>\n");
}


