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

#ifndef _VARIABLE_H_
#define _VARIABLE_H_

/* The string we use as reference to put our variables on its type.
 * If the string we deal with is bigger than this one, it will then become
 * the reference for the rest of the graph.
 */
#define STRING_TYPE_MAX "The competent programmer is fully aware of the limited size of his own skull. He therefore approaches his task with full humility, and avoids clever tricks like the plague."
/* Same value but calculated using values-mapping (_UNIT_TEST_) */
#define STRING_TYPE_MAX_YVAL 16105.00

#define EMPTY_TYPE_MAX_YVAL 1 /* Will make disorder and help folks writting better pcv file */

#define CHAR_TYPE_MAX_YVAL 255
#define SHORT_TYPE_MAX_YVAL 32767
#define INTEGER_TYPE_MAX_YVAL 65535
#define FLOAT_TYPE_MAX_YVAL INTEGER_TYPE_MAX_YVAL

#define TIMELINE_TYPE_MAX_YVAL 86399 /* 23:59 in seconds */
#define GOLDNUMBER_TYPE_MAX_YVAL 1433
#define IPV4_TYPE_MAX_YVAL 4294967295

PcvAxisY picviz_variable_max(datatype_t vartype);

#endif /* _VARIABLE_H_ */

