/*
 * props/color.c: Manage [color="red"] property
 */
#include <string.h>
#include "color.h"

char *picviz_color_named_to_hexstr(char *color)
{
        int MAX_COLORS = 13;
        char *pcolors[] = {"white","black", "red", "green", "blue", "yellow", "grey", "turquoise", "pink", "orange", "darkblue", "darkgreen", "darkred", "brown"};
        char *chart[] = {"#FFFFFF","#000000", "#FF0000", "#00FF00", "#0000FF", "#FFFF00", "#C0C0C0", "#00FFFF", "#FF0099", "#FF9900", "#3333CC", "#339933", "#990000", "#8B6969"};
        int i=0;

        for (i=0;i<=MAX_COLORS;i++) {
#ifdef DEBUG_PROPERTIES
                printf("color=[%s];pcolors[i]=[%s], value=[%s]\n", color, pcolors[i], chart[i]);
#endif
                if (!strcmp(color, pcolors[i])) {
                        return chart[i];
                }
        }

        return "#000000"; /* Color not found, we return black as default */
}

#ifdef _UNIT_TEST_
int main(void)
{
        printf("White=%s\n", picviz_color_named_to_hexstr("white"));
        printf("Red=%s\n", picviz_color_named_to_hexstr("red"));
}
#endif
