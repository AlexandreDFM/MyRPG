/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_cine_elements_spe
*/

#include "cinematics_elements.h"

cine_ele c_eles(char *tpath, sfVector2f pos, sfIntRect rect)
{
    cine_ele ele;
    ele.sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(tpath, NULL);
    ele.pos = pos;
    ele.rect = rect;
    ele.resize = (sfVector2f) {3, 3};
    sfSprite_setTexture(ele.sprite, texture, sfTrue);
    sfSprite_setPosition(ele.sprite, ele.pos);
    sfSprite_setScale(ele.sprite, ele.resize);
    sfSprite_setTextureRect(ele.sprite, ele.rect);
    return ele;
}
