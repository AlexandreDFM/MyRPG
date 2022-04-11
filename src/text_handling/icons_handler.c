/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** icons_handler
*/

#include "rpg.h"

sfIntRect find_icons(wininf *inf, char *name)
{
    int len = my_strlen(name);
    for (int i = 0; inf->atlases.icons[i]; i++) {
        // printf("%s\n", inf->atlases.icons[i]);
        if (!my_strncmp(name, inf->atlases.icons[i], len)) {
            char **arr = my_strtwa(inf->atlases.icons[i], ";\n");
            return (sfIntRect) {my_atoi(arr[1]), my_atoi(arr[2]),
                my_atoi(arr[3]), my_atoi(arr[4])};
        }
    }
    return (sfIntRect){-1, -1, -1, -1};
}

void add_icon(sfVector2i origin, sfImage *img, sfIntRect r, sfImage *atlas)
{
    for (int y = 0; y < r.height; y++) {
        for (int x = 0; x < r.width; x++) {
            sfColor col = sfImage_getPixel(atlas, r.left + x, r.top + y);
            sfImage_setPixel(img, origin.x + x, origin.y + y, col);
        }
    }
}
