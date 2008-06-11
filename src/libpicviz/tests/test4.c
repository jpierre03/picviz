#include <picviz.h>

int main(void)
{
        struct pcimage_t *image;

        picviz_init();
        image = (struct pcimage_t *)pcv_parse("test4.pcv");
//        picviz_image_debug_printall(image);

        image_to_svg(image);

        return 0;
}
