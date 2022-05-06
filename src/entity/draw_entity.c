/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** draw_entity
*/

#include "rpg.h"

void anim_entity(time_info *time_s, entity *obj)
{
    if (time_s->anim < RATE) return;
    if (obj->rect.left < obj->max && obj->sign == 1) {
        obj->rect.left += obj->width;
    } else if (obj->sign == 1) {
            obj->sign *= obj->loop_type ? -1 : 1;
            obj->rect.left = !obj->loop_type ? 0 : obj->rect.left;
    }
    if (obj->rect.left >= obj->width && obj->sign == -1) {
        obj->rect.left -= obj->width;
    } else if (obj->sign == -1) {
        obj->sign *= obj->loop_type ? -1.0f : 1.0f;
        obj->rect.left += obj->loop_type ? obj->width : 0;
    }
    sfSprite_setTextureRect(obj->sp, obj->rect);
}

void draw_entity(time_info *time_s, list *obj, sfRenderWindow *win)
{
    for (list *t = obj; t; t = t->next) {
        anim_entity(time_s, t->data);
        sfRenderWindow_drawSprite(win, ((entity*)t->data)->sp, 0);
    }
}
