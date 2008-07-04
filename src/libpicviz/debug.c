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
#include <stdarg.h>
#include <time.h>

#include <debug.h>

void picviz_debug(int level, int area, const char *format, ...)
{

        char *timestr;
        va_list ap;
        time_t tm;
        FILE *fd = stderr;

        if (level == PICVIZ_DEBUG_NOTICE) {
                fd = stdout;
        }

        va_start(ap, format);

        tm = time(NULL);
        timestr = ctime(&tm);
        timestr[strlen(timestr)-1] = '\0';
        fprintf(fd, "%s <%1.1d> ", timestr, level, area);
        vfprintf(fd, format, ap);
        va_end(ap);
        fprintf(fd, "\n");

        fflush(fd);

}

