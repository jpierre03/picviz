#include <stdio.h>
#include <stdlib.h>
#include <picviz.h>

int main(int argv, char **argc)
{
        struct pcimage_t *image;

        if (argv < 2) {
                fprintf(stderr, "Syntax: %s file.pcv\n",argc[0]);
                exit(1);
        }

        picviz_init();

        image = (struct pcimage_t *)pcv_parse(argc[1]);
        if (!image) {
                fprintf(stderr, "Cannot parse image %s\n", argc[1]);
                exit(1);
        }

        //picviz_render_image(image);
        //picviz_image_debug_printall(image);
        image_to_svg(image);

        picviz_image_destroy(image);

        return 0;
}
