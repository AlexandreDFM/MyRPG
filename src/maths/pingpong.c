/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** pingpong
*/

#include "rpg.h"

float my_clamp(float d, float min, float max)
{
    const float t = d < min ? min : d;
    return t > max ? max : t;
}

float my_repeat(float t, float mag)
{
    return my_clamp(t - floorf(t / mag) * mag, 0.0f, mag);
}

float my_pingpong(float t, float mag)
{
    t = my_repeat(t, mag * 2.0f);
    float sub = (t - mag);
    float abs = sub < 0 ? sub * -1 : sub;
    return mag - abs;
}
