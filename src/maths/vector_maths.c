/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** vector_maths
*/

#include "rpg.h"

float distance(sfVector2f a, sfVector2f b)
{
    float dst_square = pow(b.x - a.x, 2) + pow(b.y - a.y, 2);
    return sqrt(dst_square);
}
