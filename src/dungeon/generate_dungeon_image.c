/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** generate_dungeon_image
*/

#include "dungeon.h"

void texture_line(char **tab, sfVector2i ve, sfUint8 **pxs, const sfUint8 *ptr)
{
    int indexes[47] = {11, 31, 22, 107, 255, 214, 104, 248, 208, 10, 24, 18,
        66, 0, 72, 80, 2, 8, 90, 16, 64, 26, 74, 82, 88, 250, 222, 123, 95,
        254, 251, 223, 127, 106, 210, 75, 86, 30, 27, 216, 120, 91, 94,
        122, 218, 126, 219};
    sfIntRect re; sfVector2i v = (sfVector2i){ve.y, 144};
    for (int o = 0; tab[ve.x][o] != '\0'; o++) {
        unsigned char neighbours = get_neighbours(ve.x, o, tab, ve.y);
        int ind = search(indexes, neighbours, 1); ind = ind == -1 ? 4 : ind;
        char room = '.';
        if (tab[ve.x][o] == room) {
            int r = (rand() % 100) >= 25 ? 0 : 2;
            re.left = ind, re.top = ve.x, re.width = o, re.height = r;
            insert_into(pxs, ptr, re, v);
        } else {
            int r = (rand() % 100) >= 5 ? 0 : 1;
            re.left = ind, re.top = ve.x, re.width = o, re.height = r + 3;
            insert_into(pxs, ptr, re, v);
        }
    }
}

sfImage *generate_map_image(char **map, int line_len, sfImage *spritesheet)
{
    const sfUint8 *ptr = sfImage_getPixelsPtr(spritesheet);
    sfUint8 *pixls = malloc((24 * line_len) * (24 * line_len) * 4 *
    sizeof(sfUint8));
    for (int i = 0; i < (24 * line_len) * (24 * line_len) * 4; i++) {
        pixls[i] = 255;
    }
    for (int i = 0; map[i]; i++) {
        texture_line(map, (sfVector2i){i, line_len}, &pixls, ptr);
    }
    sfImage *t = sfImage_createFromPixels(24 * line_len, 24 * line_len, pixls);
    return t;
}
