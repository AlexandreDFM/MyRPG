/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** lerp
*/

#include "rpg.h"

sfVector2f my_lerp(sfVector2f a, sfVector2f b, float t)
{
    sfVector2f new_vec;
    new_vec.x = a.x + (b.x - a.x) * t;
    new_vec.y = a.y + (b.y - a.y) * t;
    return new_vec;
}
