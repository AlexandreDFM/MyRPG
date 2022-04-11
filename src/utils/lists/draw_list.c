/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** draw_list
*/

#include "rpg.h"

void draw_list(list *obj, sfRenderWindow *win)
{
    list *tmp = obj;
    while (obj) {
        sfRenderWindow_drawSprite(win, obj->data, 0);
        obj = obj->next;
    }
    obj = tmp;
}
