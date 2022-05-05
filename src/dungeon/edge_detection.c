/*
** EPITECH PROJECT, 2022
** dungeon
** File description:
** edge_detection
*/

#include "dungeon.h"

sfImage *generate_map_image(char **map, int line_len, sfImage *spritesheet)
{
    int indexes[47] = {11, 31, 22, 107, 255, 214, 104, 248, 208, 10, 24, 18,
        66, 0, 72, 80, 2, 8, 90, 16, 64, 26, 74, 82, 88, 250, 222, 123, 95,
        254, 251, 223, 127, 106, 210, 75, 86, 30, 27, 216, 120, 91, 94,
        122, 218, 126, 219};
    char **tab = map;
    const sfUint8 *ptr = sfImage_getPixelsPtr(spritesheet);
    sfUint8 *pixls = malloc((24 * line_len) * (24 * line_len) * 4 *
    sizeof(sfUint8));
    for (int i = 0; i < (24 * line_len) * (24 * line_len) * 4; i++) {
        pixls[i] = 255;
    }

    for (int i = 0; tab[i]; i++) {
        for (int o = 0; tab[i][o] != '\0'; o++) {
            unsigned char neighbours = get_neighbours(i, o, tab, line_len);
            int ind = search(indexes, neighbours, 1);
            ind = ind == -1 ? 4 : ind;
            char room = '.';
            if (tab[i][o] == room) {
                int r = (rand() % 100) >= 25 ? 0 : 2;
                insert_into(&pixls, ind, i, o, ptr, r, line_len, 144);
            } else {
                int r = (rand() % 100) >= 5 ? 0 : 1;
                insert_into(&pixls, ind, i, o, ptr, 3 + r, line_len, 144);
            }
        }
    }
    sfImage *t = sfImage_createFromPixels(24 * line_len, 24 * line_len, pixls);
    return t;
}

void insert_into(sfUint8 **pixels, int index, int start_x, int start_y, const
sfUint8 *ptr, int y, int line_len, int ref_len)
{
    for (int x = 0; x < 24; x += 1) {
        for (int i = 0; i < 24 * 4; i++) {
            (*pixels)[(i + (24 * 4) * start_y) + (x + 24 * start_x) *
            (24 * line_len * 4)] = ptr[i + (x + 24 * index) * (ref_len * 4)
            + 24 * 4 * y];
        }
    }
}

unsigned char get_neighbours(int i, int o, char **tab, int len)
{
    unsigned char bits = 0;
    for (int y = -1; y != 2; y++) {
        for (int x = -1; x != 2; x++) {
            if (i + y < 0 || o + x < 0 || i + y > len - 1 || o + x > len - 1) {
                bits = bits << 1;
                bits |= 1;
            } else {
                if (!(x == 0 && y == 0)) {
                    if (tab[i + y][o + x] == tab[i][o]) {
                        bits = bits << 1;
                        bits |= 1;
                    } else {
                        bits = bits << 1;
                        bits |= 0;
                    }
                }
            }
        }
    }
    return bits;
}

int search(int array[], int x, int started) {
    for (int ind = 0; ind < 47; ind++) {
        if (array[ind] == x) {
            return ind;
        }
    }
    if (started) {
        if (x == 159 || x == 63) {
            return 1;
        } else if (x == 124 || x == 252 || x == 249) {
            return 7;
        } else if (x == 246 || x == 215 || x == 247) {
            return 5;
        } else if (x == 235 || x == 111 || x == 203) {
            return 3;
        } else if (x == 240 || x == 212){
            return 8;
        } else if (x == 15 || x == 43) {
            return 0;
        } else if (x == 23 || x == 150) {
            return 2;
        } else if (x == 192 || x == 96 || x == 224) {
            return 20;
        } else if (x == 188 || x == 185 || x == 153 || x == 156 || x == 57 ||
        x == 60 || x == 25 || x == 28 || x == 152 || x == 56) {
            return 10;
        } else if (x == 232 || x == 105) {
            return 6;
        } else if (x == 71 || x == 98 || x == 99 || x == 2 || x == 70 ||
        x == 194 || x == 67 || x == 226 || x == 195) {
            return 12;
        } else if (x == 234) {
            return 33;
        } else if (x == 59) {
            return 38;
        } else if (x == 148 || x == 144 || x == 20) {
            return 19;
        } else if (x == 7 || x == 3 || x == 6) {
            return 16;
        } else if (x == 40 || x == 9 || x == 41) {
            return 17;
        } else if (x == 79) {
            return 35;
        } else if (x == 220) {
            return 39;
        } else if (x == 242 || x == 211) {
            return 34;
        } else if (x == 158) {
            return 37;
        } else if (x == 121) {
            return 40;
        } else if (x == 84) {
            return 36;
        }
        return 4;
    }
    return 0;
}
