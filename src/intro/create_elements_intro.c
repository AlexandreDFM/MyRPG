/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_elements_intro
*/

#include "intro.h"

sfSprite *atlas_to_sprite_full(sfIntRect rect, sfImage *atlas)
{
    sfSprite *sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromImage(atlas, NULL);
    sfSprite_setTexture(sprite, texture, sfFalse);
    return sprite;
}

cine_ele c_ele(sfImage *img, sfVector2f pos, sfIntRect rect, sfVector2f size)
{
    cine_ele ele;
    ele.sprite = atlas_to_sprite_full(rect, img);
    ele.pos = pos;
    // ele.rect = (sfIntRect) {0, 0, rect.width, rect.top};
    ele.rect = rect;
    ele.resize = size;
    sfSprite_setPosition(ele.sprite, ele.pos);
    sfSprite_setScale(ele.sprite, ele.resize);
    return ele;
}
