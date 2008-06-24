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

        for ( i = 0; i <= PICVIZ_MAX_AXES; i++) {
                string_max[i] = picviz_variable_max(DATATYPE_STRING);
        }

        if (! engine.__axis_label_exists) {
                image->header_height = 0;
        }


        llist_for_each_entry(line, &image->lines->list, list) {
                llist_for_each_entry(axisplot, &line->axisplot->list, list) {
                        struct axis_t *axis = (struct axis_t *)picviz_axis_get(image, axisplot->axis_id);

                        if (axis->type == DATATYPE_STRING) {
                                strheight = picviz_line_value_get_from_string_dummy(axis->type, axisplot->strval);
                                if (strheight > string_max[axisplot->axis_id]) {
                                        string_max[axisplot->axis_id] = strheight;
                                }
                        }

                        maxval = picviz_variable_max(axis->type);

                        strheight = picviz_line_value_get_from_string_dummy(axis->type, axisplot->strval);
                        if (axis->type == DATATYPE_STRING) {
                                mappedval = picviz_values_mapping_get_from_y(image, string_max[axisplot->axis_id], strheight);
                        } else {
                                mappedval = picviz_values_mapping_get_from_y(image, maxval, strheight);
                        }

                        axisplot->y = mappedval;
                }
        }

}
