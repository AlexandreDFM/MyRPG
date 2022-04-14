/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** set_cursor
*/

#include "rpg.h"

sfSprite *set_cursor(wininf *inf, sfVector2f scale, sfVector2f pos)
{
    sfIntRect r = {1232, 855, 10, 8};
    sfSprite *cursor = atlas_to_sprite(r, inf->atlases.atlas);
    r.left = 0; r.top = 0; r.width = 5;
    sfSprite_setScale(cursor, scale);
    sfSprite_setPosition(cursor, pos);
    return cursor;
}
