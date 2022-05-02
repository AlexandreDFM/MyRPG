/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** display_elements_spe
*/

#include "cinematics_elements.h"

void display_eles(sfRenderWindow *window, cine_ele ele)
{
    sfSprite_setPosition(ele.sprite, ele.pos);
    sfSprite_setTextureRect(ele.sprite, ele.rect);
    sfSprite_setScale(ele.sprite, ele.resize);
    sfRenderWindow_drawSprite(window, ele.sprite, NULL);
}
