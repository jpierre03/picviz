#include <stdio.h>
#include <stdlib.h>
#include <pcimage.h>

#include "pcimage.h"
#include "defaults.h"
#include "axis.h"
#include "image.h"
#include "engine.h"

/**
 * \ingroup PicvizMain
 * @{
 */

/** \file image.c
 * \brief Create and manipulate a parallel coordinates image
 */

struct engine_t engine;

/**
 * Creates a new parallel coordinates empty image
 *
 * \return the new picviz image or NULL on error
 */
struct pcimage_t *picviz_image_new(void)
{
        struct pcimage_t *pcimage = NULL;

        pcimage = malloc(sizeof(*pcimage));
        if ( ! pcimage ) {
                fprintf(stderr, "Cannot create image: memory exhausted.\n");
                return NULL;
        }
        pcimage->height        = DEFAULT_IMAGE_HEIGHT;
        pcimage->header_height = DEFAULT_IMAGE_HEADER_HEIGHT;
	pcimage->width         = 0;
        pcimage->zero_pos      = TOP;
	pcimage->bg_color      = "";
        pcimage->axes          = (struct axis_t *)picviz_axis_new();
        pcimage->lines         = (struct line_t *)picviz_line_new();

        return pcimage;
}

void picviz_image_destroy(struct pcimage_t *image)
{
        picviz_axis_destroy(image);

        //free(image->lines->props->color);
        free(image->lines->props);
        free(image->lines->axisplot);
        free(image->lines);
        free(image);
}

/**
 * Increases image width
 *
 * \param i the image to update
 * \param expand width value to increase
 */
void picviz_image_width_increase(struct pcimage_t *i, unsigned int expand)
{
        i->width += expand;
}

struct axis_t *picviz_image_axes_get(struct pcimage_t *i)
{
        return i->axes;
}

void picviz_image_axis_append(struct pcimage_t *i, struct axis_t *axis)
{
        picviz_image_width_increase(i, engine.axis_default_space);
        axis->xpos = engine.axis_x_cursor;
        engine.axis_x_cursor += engine.axis_default_space;
        llist_add_tail(&axis->list, &i->axes->list);
}

void picviz_image_line_append(struct pcimage_t *image, struct line_t *line)
{
        llist_add_tail(&line->list, &image->lines->list);
}

void picviz_image_debug_printall(struct pcimage_t *i)
{
        struct axis_t *a;
        struct line_t *l;
        struct axisplot_t *axisplot;

        printf("i->width=%d\n", i->width);
        printf("i->height=%d\n", i->height);
        printf("i->header_height=%d\n", i->header_height);
        printf("i->zero_pos=%d\n", i->zero_pos);
        printf("i->bg_color=%s\n", i->bg_color);
        llist_for_each_entry(a, &i->axes->list, list) {
                printf("    a->id=%d\n", a->id);
                printf("    a->label=%s\n", a->props->label);
                printf("    a->type=%d\n", a->type);
                printf("    a->xpos=%d\n", a->xpos);
                printf("\n");
        }
        llist_for_each_entry(l, &i->lines->list, list) {
                printf("l->id=%d\n", l->id);
                printf("l->props->color=%s\n", l->props->color);
                llist_for_each_entry(axisplot, &l->axisplot->list, list) {
                        printf("    axisplot->strval=%s\n", axisplot->strval);
                        printf("    axisplot->y=%d\n", axisplot->y);
                        printf("    axisplot->axis_id=%d\n", axisplot->axis_id);
                }
        }
}

void picviz_init(void)
{
        engine.axis_default_thickness = 1;
        engine.axis_default_space = 100;
        engine.axis_x_cursor = engine.axis_default_space / 2;
        engine.__axis_label_exists = 0;
        engine.zero_position = TOP;
        engine.display_raw_data = 0;

        //fprintf(stdout, "Picviz - (c) 2008 Sebastien Tricaud\n");
        //fprintf(stdout, "[+] Loaded render plugins:\n");
        //fprintf(stdout, "[+] Loaded output plugins: svg\n");

}

#ifdef _UNIT_TEST_
int main(void)
{
        struct pcimage_t *image;
        struct axis_t *axis;
        struct line_t *line;
        int i = 0;
        float value;

        picviz_init();
        image = picviz_image_new();
        axis = picviz_axis_init();
        picviz_image_axis_append(image, axis);
        picviz_axis_set_type_from_string(axis, "string");
        value = picviz_line_value_get_from_string(axis, NULL, "foo");
        printf("value=%f\n", value);
        picviz_axis_prop_set_label(axis, "foo");
        line = picviz_line_init();
        picviz_axis_line_append(axis, line);
        axis = picviz_axis_init();
        picviz_image_axis_append(image, axis);
        picviz_axis_set_type_from_string(axis, "integer");
        picviz_axis_prop_set_label(axis, "bar");
        line = picviz_line_init();
        picviz_axis_line_append(axis, line);
        line = picviz_line_init();
        picviz_axis_line_append(axis, line);

        picviz_image_debug_printall(image);

}
#endif

/**
 * @}
 */

