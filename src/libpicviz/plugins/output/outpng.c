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

#include <plplot.h>


void output(pcimage_t *i)
{
        struct axis_t *a;
        struct line_t *l;
        struct axisplot_t *axisplot;

        PcvWidth  last_x = -1;
        PcvHeight last_y = -1;

	PLFLT plx[PICVIZ_MAX_AXES], ply[PICVIZ_MAX_AXES];

	unsigned long n = 0;
	unsigned long an, ln;
	unsigned int apos = 0;
	unsigned int axisn = 1;

	plsdev("pngcairo");
	plscolbg(255,255,255);
	plinit();


        llist_for_each_entry(a, &i->axes->list, list) {
		n++;
        }


	plenv(0, n-1, 0, i->height, 0, -2);
	plcol0(9); // Lines in blue

        /* Axes */
        llist_for_each_entry(a, &i->axes->list, list) {
		pljoin(a->id-1, 0, a->id-1, i->height);
	}


        llist_for_each_entry(l, &i->lines->list, list) {
		apos = 0;
		axisn=0;

                llist_for_each_entry(axisplot, &l->axisplot->list, list) {
			plx[apos] = axisn;
			ply[apos] = axisplot->y;

			apos++;
			axisn++;
                }

		plline(apos, plx, ply);

        }


	plend();

}


