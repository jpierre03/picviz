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
//        int nb_axes = 0;
        int i = 0;
        int nb_types = sizeof(datatype_t);
        PcvAxisY string_max[PICVIZ_MAX_AXES];
        PcvAxisY maxval;

        int axis_label_exists = 0;

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
                        axisplot->y = picviz_values_mapping_get_from_y(image, maxval,
                                                picviz_line_value_get_from_string_dummy(axis->type, axisplot->strval)
                                        );
                }
        }

//#endif

#if 0
        /* Recalculate values */
        llist_for_each_entry(line, &image->lines->list, list) {
                llist_for_each_entry(axisplot, &line->axisplot->list, list) {
                        struct axis_t *axis = (struct axis_t *)picviz_axis_get(image, axisplot->axis_id);
                        axisplot->y = picviz_values_mapping_get_from_y(image, maxval, axisplot->y);
                }
        }
#endif
#if 0
// Take the max value per axis
// it can be an wanted behavior
// but I don't like it
        for ( i = 1; i <= nb_axes; i++ ) {
                max[i] = picviz_line_max_get(image->lines, i);
                //printf("MAX FOR %d: %.2f\n", i, max);
        }

        llist_for_each_entry(line, &image->lines->list, list) {
                llist_for_each_entry(axisplot, &line->axisplot->list, list) {
                        axisplot->y = picviz_values_mapping_get_from_y(image, max[axisplot->axis_id], axisplot->y);
                }
        }
#endif

//        printf("MAX = %.2f\n", max);

}
