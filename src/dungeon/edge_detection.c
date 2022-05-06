/*
** EPITECH PROJECT, 2022
** dungeon
** File description:
** edge_detection
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

void insert_into(sfUint8 **pxs, const sfUint8 *ptr, sfIntRect r, sfVector2i v)
{
    for (int x = 0; x < 24; x += 1) {
        for (int i = 0; i < 24 * 4; i++) {
            (*pxs)[(i + (24 * 4) * r.width) + (x + 24 * r.top) *
            (24 * v.x * 4)] = ptr[i + (x + 24 * r.left) * (v.y * 4)
            + 24 * 4 * r.height];
        }
    }
}

void get_diags_bit(sfIntRect r, char **tab, unsigned char *bits, int x)
{
    if (!(x == 0 && r.top == 0)) {
        if (tab[r.left + r.top][r.width + x] == tab[r.left][r.width]) {
            *bits = *bits << 1;
            *bits = *bits | 1;
        } else {
            *bits = *bits << 1;
            *bits |= 0;
        }
    }
}

void get_neighbours_bitx(sfIntRect r, char **tab, unsigned char *bits)
{
    for (int x = -1; x != 2; x++) {
        int cond = r.left + r.top < 0 || r.width + x < 0;
        int sum = r.left + r.top;
        if (cond || sum > r.height - 1 || r.width + x > r.height - 1) {
            *bits = *bits << 1;
            *bits |= 1;
        } else {
            get_diags_bit(r, tab, bits, x);
        }
    }
}

unsigned char get_neighbours(int i, int o, char **tab, int len)
{
    unsigned char bits = 0;
    for (int y = -1; y != 2; y++) {
        get_neighbours_bitx((sfIntRect){i, y, o, len}, tab, &bits);
    }
    return bits;
}

int continue_exeption(int x)
{
    if (x == 188 || x == 185 || x == 153 || x == 156 || x == 57 ||
    x == 60 || x == 25 || x == 28 || x == 152 || x == 56) return 10;
    if (x == 232 || x == 105) return 6;
    if (x == 71 || x == 98 || x == 99 || x == 2 || x == 70 ||
    x == 194 || x == 67 || x == 226 || x == 195) return 12;
    if (x == 148 || x == 144 || x == 20) return 19;
    if (x == 7 || x == 3 || x == 6) return 16;
    if (x == 40 || x == 9 || x == 41) return 17;
    if (x == 79) return 35;
    if (x == 220) return 39;
    if (x == 242 || x == 211) return 34;
    if (x == 158) return 37;
    if (x == 121) return 40;
    if (x == 84) return 36;
    return 4;
}

int search(int array[], int x, int started) {
    for (int ind = 0; ind < 47; ind++) {
        if (array[ind] == x) {
            return ind;
        }
    }
    if (started) {
        if (x == 159 || x == 63) return 1;
        if (x == 124 || x == 252 || x == 249) return 7;
        if (x == 246 || x == 215 || x == 247) return 5;
        if (x == 235 || x == 111 || x == 203) return 3;
        if (x == 240 || x == 212) return 8;
        if (x == 15 || x == 43) return 0;
        if (x == 23 || x == 150) return 2;
        if (x == 192 || x == 96 || x == 224) return 20;
        if (x == 234) return 33;
        if (x == 59) return 38;
        return continue_exeption(x);
    }
    return 0;
}
