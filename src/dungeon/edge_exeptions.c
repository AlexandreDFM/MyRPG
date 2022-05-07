/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** edge_exeptions
*/

#include "dungeon.h"

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
