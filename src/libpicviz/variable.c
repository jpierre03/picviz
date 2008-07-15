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

#include <picviz.h>

//PcvHeight picviz_variable_max(datatype_t vartype)
PcvHeight picviz_variable_max(int vartype)
{

        switch (vartype) {
                case DATATYPE_EMPTY:
                        return EMPTY_TYPE_MAX_YVAL;
                case DATATYPE_SHORT:
                        return SHORT_TYPE_MAX_YVAL;
                case DATATYPE_INTEGER:
                        return INTEGER_TYPE_MAX_YVAL;
                case DATATYPE_FLOAT:
                        return FLOAT_TYPE_MAX_YVAL;
                case DATATYPE_STRING:
                        return STRING_TYPE_MAX_YVAL;
                case DATATYPE_TIMELINE:
                        return TIMELINE_TYPE_MAX_YVAL;
                case DATATYPE_IPV4:
                        return IPV4_TYPE_MAX_YVAL;
                case DATATYPE_CHAR:
                        return CHAR_TYPE_MAX_YVAL;
                case DATATYPE_GOLD:
                        return GOLDNUMBER_TYPE_MAX_YVAL;

        }
}
