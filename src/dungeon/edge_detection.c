/*
** EPITECH PROJECT, 2022
** dungeon
** File description:
** edge_detection
*/

#include "dungeon.h"

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
