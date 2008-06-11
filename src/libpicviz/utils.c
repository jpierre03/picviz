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

/* Utils functions for plugins */
#include <stdlib.h>
#include <linuxlist.h>

#include "utils.h"

typedef struct alllines_t {
	struct llist_head list;
	int x1;
        int x2;
        float y1;
        float y2;
} alllines_t;

LLIST_HEAD(lc_list); /* Lines coordinates list */

void picviz_util_line_append(int x1, float y1, int x2, float y2)
{
	struct alllines_t *alllines;

	alllines = malloc(sizeof(*alllines));

	alllines->x1 = x1;
	alllines->y1 = y1;
	alllines->x2 = x2;
	alllines->y2 = y2;

	llist_add_tail(&alllines->list, &lc_list);
}

/* Add lines x1, x2, y1, y2 to a list, to avoid duplicates */
int picviz_util_line_exists(int x1, float y1, int x2, float y2)
{
        struct alllines_t *alllines;

	llist_for_each_entry(alllines, &lc_list, list) {
                if ((alllines->x1 == x1) &&
                    (alllines->y1 == y1) &&
                    (alllines->x2 == x2) &&
                    (alllines->y2 == y2)) {
                        return 1;
                    }
	}

        return 0;
}


