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

#ifndef COMMON_H
#define COMMON_H

#define TRUE 1
#define FALSE 0

#define min(x, y) ({ \
        typeof(x) _x = (x);  typeof(y) _y = (y); \
        _x < _y ? _x : _y; })
#define max(x, y) ({ \
        typeof(x) _x = (x);  typeof(y) _y = (y); \
        _x > _y ? _x : _y; })

#define MSEC    * 1
#define SEC	* 1000 MSEC
#define MIN	* 60 SEC
#define HOUR	* 60 MIN
#define DAY	* 24 HOUR

#endif

