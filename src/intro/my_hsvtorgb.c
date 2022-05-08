/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** my_hsvtorgb
*/

#include "intro.h"

sfColor my_hsvtorgb(float h2, float s2, float v2)
{
    float s = s2 / 100, v = v2 / 100; float c = s * v;
    float m = v - c, r, g, b, x = c * (1 - fabs(fmod(h2 / 60.0, 2) -1));
    while (1) {
        if (h2 >= 0 && h2 < 60) {
            r = c, g = x, b = 0; break;
        } else if (h2 >= 60 && h2 < 120) {
            r = x, g = c, b = 0; break;
        }
        if (h2 >= 120 && h2 < 180) {
            r = 0, g = c, b = x; break;
        } else if (h2 >= 180 && h2 < 240) {
            r = 0, g = x, b = c; break;
        }
        if (h2 >= 240 && h2 < 300) {
            r = x, g = 0, b = c; break;
        } r = c, g = 0, b = x; break;
    } int rr = (r + m) * 255, gg = (g + m) * 255, bb = (b + m) * 255;
    sfColor color = {rr, gg, bb, 255}; return color;
}
