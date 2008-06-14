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
#include <math.h>

#include <picviz.h>
#include <linuxlist.h>


void picviz_render_image(pcimage_t *image)
{
        struct axis_t *axis;
        struct line_t *line;
        struct axisplot_t *axisplot;
        int i = 0;
        int nb_types = sizeof(datatype_t);
        PcvHeight string_max[PICVIZ_MAX_AXES];
        PcvHeight maxval;

        int axis_label_exists = 0;

        PcvHeight strheight;
        PcvHeight mappedval;


        llist_for_each_entry(axis, &image->axes->list, list) {
                if (strcmp(axis->props->label, "")) {
                        axis_label_exists = 1;
                }
                string_max[i] = picviz_line_max_get(image->lines, i);
                i++;
        }

        if (!axis_label_exists) {
                image->header_height = 0;
        }

        /* Set Y values */
        llist_for_each_entry(line, &image->lines->list, list) {
                llist_for_each_entry(axisplot, &line->axisplot->list, list) {
                        struct axis_t *axis = (struct axis_t *)picviz_axis_get(image, axisplot->axis_id);
                        maxval = picviz_variable_max(axis->type);
                        if (axis->type == DATATYPE_STRING) {
                                if (string_max[axisplot->axis_id] > picviz_variable_max(axis->type)) {
                                        maxval = string_max[axisplot->axis_id];
                                }
                        }

                        strheight = picviz_line_value_get_from_string_dummy(axis->type, axisplot->strval);
                        mappedval = picviz_values_mapping_get_from_y(image, maxval, strheight);

                        axisplot->y = mappedval;
                }
        }
}
