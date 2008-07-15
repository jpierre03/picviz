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

#ifndef _ENGINE_H_
#define _ENGINE_H_

#ifdef __cplusplus
 extern "C" {
#endif

enum position_t {
        TOP,
        MIDDLE,
        BOTTOM
} position_t;

typedef struct engine_t {
        /* Private members: not recommended to change this at all! */
        char __axis_label_exists; /* Defines wether we have labels in our axis or not */
        char __header_title_exists; /* Defines wether we have title in our graph */

        unsigned int axis_default_thickness;
        unsigned int axis_x_cursor; /* We move where the X pos of the axis must be put everytime we add one */
        unsigned int axis_default_space;
        enum position_t zero_position;
        int display_raw_data;

} engine_t;


extern struct engine_t engine;

#ifdef __cplusplus
 }
#endif

#endif /* _ENGINE_H_ */
