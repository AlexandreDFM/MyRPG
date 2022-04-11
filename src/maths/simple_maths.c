/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** simple_maths
*/

#include "rpg.h"

float my_lerpf(float a, float b, float t)
{
    return a + (b - a) * t;
}

float manhattan_distance(sfVector2f a, sfVector2f b)
{
    return (fabsf(a.x - b.x) + fabsf(a.y - b.y));
}
