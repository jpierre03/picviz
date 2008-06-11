#include <picviz.h>

int main(void)
{
        struct pcimage_t *image;

        picviz_init();
        image = (struct pcimage_t *)pcv_parse("test-colors.pcv");
        image_to_svg(image);
        return 0;
}
