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

#ifndef _LINE_H_
#define _LINE_H_

//#include <picviz.h>
#include "types.h"
#include "pcimage.h"

#ifdef __cplusplus
 extern "C" {
#endif

struct line_properties_t *picviz_line_properties_new(void);
struct line_t *picviz_line_init(void);
struct line_t *picviz_line_new(void);
struct line_t *picviz_line_get(struct axis_t *axis, PcvID id);
void picviz_line_prop_color_set(struct line_t *line, PcvString color);
char *picviz_line_prop_color_get(struct line_t *line);
void picviz_lines_axisplot_append(struct line_t *line, struct axisplot_t *axisplot);
PcvHeight picviz_line_max_get(struct line_t *line, PcvID axis_id);
PcvHeight picviz_line_max_pertype_get(struct pcimage_t *image, datatype_t type);

#ifdef __cplusplus
 }
#endif

#endif /* _LINE_H_ */
