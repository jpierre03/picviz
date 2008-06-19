#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <picviz.h>

int main(int argv, char **argc)
{
        struct pcimage_t *image;

        if (argv < 2) {
                fprintf(stderr, "Syntax: %s file.pcv [-debug|-render]\n",argc[0]);
                exit(1);
        }

        picviz_init();

        image = (struct pcimage_t *)pcv_parse(argc[1]);
        if (!image) {
                fprintf(stderr, "Cannot parse image %s\n", argc[1]);
                exit(1);
        }

        if (argv == 2) {
                image_to_svg(image);
        } else {
                if ( ! strcmp(argc[2], "-debug") ) {
                        picviz_image_debug_printall(image);
                } else if ( ! strcmp(argc[2], "-render") ) {
                        picviz_render_image(image);
                        picviz_image_debug_printall(image);
                } else if ( ! strcmp(argc[2], "-raw")) {
                        engine.display_raw_data = 1;
                        image_to_svg(image);
                } else {
                        fprintf(stderr, "Unknown parameter %s\n", argc[2]);
                }
        }

        picviz_image_destroy(image);

        return 0;
}
