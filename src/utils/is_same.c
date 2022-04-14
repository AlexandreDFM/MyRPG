/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** is_same
*/

#include "rpg.h"

int is_same(sfVector2f a, sfVector2f b, float d)
{
    int diffx = a.x - b.x;
    int diffy = a.y - b.y;
    return (diffx <= d && diffx >= -d && diffy <= d && diffy >= -d);
}
