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

#ifndef _AXIS_H_
#define _AXIS_H_

#include <pcimage.h>

struct axis_properties_t *picviz_axis_properties_new(void);
struct axis_t *picviz_axis_init(void);
void picviz_axis_destroy(struct pcimage_t *image);
struct axis_t *picviz_axis_new(void);
void picviz_axis_set_type_from_string(struct axis_t *axis, char *string);
void picviz_axis_set_label(struct axis_t *axis, char *label);
struct axisplot_t *picviz_axisplot_new(void);

#endif

