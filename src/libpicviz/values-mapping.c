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
#include <sys/types.h>

#include <picviz.h>


/* Function quadtonum gladly stolen from the Gip project
 * and subject of the following license:
 * -
 * Copyright (c) 2003 Simon Ekstrand
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * -
 * Please note that this function only is subject of this license, not the
 * entire file.
 */
u_int32_t ipstr2i(char *quad)
{
	char buf[128];
	int x, y, z;
        u_int32_t i;


	//if (!validate_v4addr (quad))
	//	return -1;

	bzero ((char *) buf, 128);
	x = 0;
	while (quad[x] != '.') {
		buf[x] = quad[x];
		x++;
	}
	i = 0;
	x++;
	for (y = 0; y < 4; y++) {
		z = atoi (buf);
		if (z > 255 || z < 0)
			return -1;
		i = i | (z << (8 * (3 - y)));
		bzero ((char *) buf, 128);
		z = 0;
		while (quad[x] != '.' && quad[x] != '\0' && x < strlen (quad)) {
			buf[z] = quad[x];
			x++;
			z++;
		}
		x++;
	}

        return i;
}

/*
 * We first calculate values without caring of that axis min and max
 */
PcvHeight picviz_line_value_get_from_string_dummy(datatype_t type, char *string)
{
        float factor = 0;
        size_t strsize;
        char *hour;
        char *min;

        switch (type) {
                case DATATYPE_EMPTY:
                        break;
                case DATATYPE_SHORT:
                        factor = atoi(string);
                        break;
                case DATATYPE_INTEGER:
                        factor = atoi(string);
                        break;
                case DATATYPE_FLOAT:
                        factor = strtof(string, NULL);
                        break;
                case DATATYPE_STRING:
                        while (*string++) {
                                char c = *string;
                                factor += c;
                        }
                        break;
                case DATATYPE_TIMELINE:
                        strsize = strlen(string);
                        if (strsize == 5) { /* 10:42 */
                                hour = malloc(3);
                                min  = malloc(3);

                                strncpy(hour, string, 2);
                                hour[2] = '\0';
                                strncpy(min, string + 3, 2);
                                min[2] = '\0';

                                factor = (PcvHeight)((atoi(hour) * 60) * 60) + (atoi(min) * 60);

                                free(hour);
                                free(min);
                        }
                        break;
                case DATATYPE_IPV4:
                        factor = (PcvHeight)ipstr2i(string);
                        break;
                case DATATYPE_GOLD:
                        factor = (PcvHeight)atoi(string);
                        break;
                case DATATYPE_CHAR:
                        factor = (PcvHeight)atoi(string);
                        break;
                default:
                        fprintf(stderr, "Cannot map value from choosen variable\n");
        }

        return factor;
}

PcvHeight picviz_values_mapping_get_from_y(struct pcimage_t *image, PcvHeight max_val, PcvHeight y)
{

        return ((image->height - image->header_height) / max_val) * y;

}

#ifdef _UNIT_TEST_
#include <stdio.h>

int main(void)
{
        PcvHeight f;
        int i;

        f = picviz_line_value_get_from_string_dummy(DATATYPE_STRING, STRING_TYPE_MAX);
        i = ipstr2i("192.168.0.12");
        printf("i=%d\n", i);

        return 0;
}
#endif

