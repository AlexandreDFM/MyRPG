/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** collision_check
*/

#include "rpg.h"

int check_circle_col(collision *s, sfVector2f pos)
{
    if (manhattan_distance(pos, (sfVector2f){s->pos.x, s->pos.y}) >= 100)
        return (3);
    return !(distance((sfVector2f){s->pos.x, s->pos.y}, pos) <= s->radius);
}


int check_rect_col(collision *s, sfVector2f pos)
{
    int x_cond = pos.x >= s->pos.x && pos.x <= s->pos.x + s->size.x;
    int y_cond = pos.y >= s->pos.y && pos.y <= s->pos.y + s->size.y;
    if (x_cond && y_cond) {
        return s->ptr != -1 ? 2 : 0;
    }
    return 1;
}

int check_if_valid_movement(list *cols, sfVector2f pos, sfVector2f *vel, wininf *win, player p)
{
    int res_x = 0, res_y = 0;
    int inside = 0;
    for (list *t = cols; t; t = t->next) {
        sfVector2f x_axis = (sfVector2f){pos.x + vel->x, pos.y};
        sfVector2f y_axis = (sfVector2f){pos.x, pos.y + vel->y};
        collision *c = t->data;
        res_x = c->check(c, x_axis);
        res_y = c->check(c, y_axis);
        if (res_x != 3 && res_y != 3)
            c->draw(c, win->win);
        if (!res_x && !res_y)
            return 0;
        if (res_x && !res_y)
            vel->y = 0.0f;
        else if (!res_x && res_y)
            vel->x = 0.0f;
        if ((res_x == 2 || res_y == 2) && (c->ptr != -1)) {
            inside = 1;
            if (c->auto_trigger && !win->inputs.interact) continue;
            if (win->inputs.can_interact) continue;
            win->inputs.can_interact = 1;
            win->triggers[c->ptr](win, p);
        }
    }
    if (!inside) {
        win->inputs.can_interact = 0;
    }
    return 1;
}
