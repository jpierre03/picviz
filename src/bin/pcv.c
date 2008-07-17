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
#include <stdlib.h>
#include <string.h>
#include <picviz.h>

int main(int argv, char **argc)
{
        struct pcimage_t *image;
	char plugin_str[1024];
	char *plugin_arg;

        if ((argv < 3) || ( ! strcmp(argc[1], "--help") )) {
                fprintf(stderr, "Syntax: %s -Tplugin file.pcv [-debug|-render|-raw]\n",argc[0]);
		fprintf(stderr, "\n  Example: %s -Tsvg file.pcv -raw > out.svg\n\n", argc[0]);
                exit(1);
        }

        picviz_init();

        image = (struct pcimage_t *)pcv_parse(argc[2]);
        if (!image) {
                fprintf(stderr, "Cannot parse image %s\n", argc[1]);
                exit(1);
        }

	plugin_arg = strtok(argc[1], "-T");
	sprintf(plugin_str, "libpicvizout%s.so", plugin_arg);
        if (argv == 3) {
                picviz_plugin_load(plugin_str, image);
        } else {
                if ( ! strcmp(argc[3], "-debug") ) {
                        picviz_image_debug_printall(image);
                } else if ( ! strcmp(argc[3], "-render") ) {
                        picviz_render_image(image);
                        picviz_image_debug_printall(image);
                } else if ( ! strcmp(argc[3], "-raw")) {
                        engine.display_raw_data = 1;
                        picviz_plugin_load(plugin_str, image);
                } else {
                        fprintf(stderr, "Unknown parameter %s\n", argc[2]);
                }
        }

        picviz_image_destroy(image);

        return 0;
}
