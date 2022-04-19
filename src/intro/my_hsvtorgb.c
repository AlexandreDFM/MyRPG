/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** my_hsvtorgb
*/

#include "intro.h"

sfColor my_hsvtorgb(float H, float S, float V)
{
    float s = S / 100;
    float v = V / 100;
    float C = s * v;
    float X = C * (1 - fabs(fmod(H / 60.0, 2) -1));
    float m = v - C;
    float r, g, b;
    if (H >= 0 && H < 60) {
        r = C, g = X, b = 0;
    }
    else if (H >= 60 && H < 120) {
        r = X, g = C, b = 0;
    }
    else if (H >= 120 && H < 180) {
        r = 0, g = C, b = X;
    }
    else if (H >= 180 && H < 240) {
        r = 0, g = X, b = C;
    }
    else if (H >= 240 && H < 300) {
        r = X, g = 0, b = C;
    }
    else {
        r = C,g = 0,b = X;
    }
    int R = (r+m)*255;
    int G = (g+m)*255;
    int B = (b+m)*255;
    // printf("%f %f %f\n", r+m, g+m, b+m);
    printf("%d %d %d\n", R, G, B);
    sfColor color = {R, G, B, 255};
    return color;
}
