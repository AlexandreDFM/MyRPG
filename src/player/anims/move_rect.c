/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** move_rect
*/

#include "rpg.h"

sfIntRect move_rect_player(player p)
{
    p.r.left += p.offset;
    if (p.r.left >= p.limit.y) {
        p.r.left = p.limit.x;
    }
    sfSprite_setTextureRect(p.test, p.r);
    return p.r;
}
