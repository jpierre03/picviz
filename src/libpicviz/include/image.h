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

#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "pcimage.h"

#ifdef __cplusplus
 extern "C" {
#endif

struct pcimage_t *picviz_image_new(void);
void picviz_image_destroy(struct pcimage_t *image);
void picviz_init(void);
void picviz_image_axis_append(struct pcimage_t *i, struct axis_t *axis);
void picviz_image_line_append(struct pcimage_t *image, struct line_t *line);

#ifdef __cplusplus
 }
#endif

#endif /* _IMAGE_H_ */
