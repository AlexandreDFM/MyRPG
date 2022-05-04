/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_sprite_from_atlas
*/

#include "rpg.h"

sfSprite *atlas_to_sprite(sfIntRect rect, sfImage *atlas)
{
    sfSprite *sprite = my_sprite();
    sfTexture *texture = sfTexture_createFromImage(atlas, &rect);
    sfSprite_setTexture(sprite, texture, sfFalse);
    return sprite;
}
