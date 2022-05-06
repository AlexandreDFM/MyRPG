/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** collision_check
*/

#include "rpg.h"

int check_circle_col(collision *s, sfVector2f pos)
{
    if (manhattan_distance(pos, (sfVector2f){s->pos.x, s->pos.y}) >= 70.0f)
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

int check_collisions_conds(sfVector2i res, sfFloatRect *r, collision *c)
{
    if (!res.x && !res.y)
        return 1;
    if (res.x && !res.y)
        r->height = 0.0f;
    else if (!res.x && res.y)
        r->width = 0.0f;
    return 0;
}

int is_valid(list *col, sfFloatRect *r, wininf *inf, player *p)
{
    int res_x = 0, res_y = 0, inside = 0;
    for (list *t = col; t; t = t->next) {
        sfVector2f x_axis = (sfVector2f){r->left + r->width, r->top};
        sfVector2f y_axis = (sfVector2f){r->left, r->top + r->height};
        collision *c = t->data;
        res_x = c->check(c, x_axis); res_y = c->check(c, y_axis);
        if (res_x != 3 && res_y != 3 && inf->settings->show_collision)
            c->draw(c, inf->win);
        if (check_collisions_conds((sfVector2i){res_x, res_y}, r, c))
            return 0;
        if (!((res_x == 2 || res_y == 2) && (c->ptr != -1))) continue;
        inside = 1;
        if (c->auto_trigger && !inf->inputs.interact) continue;
        if (inf->inputs.can_interact) continue;
        inf->inputs.can_interact = 1; inf->triggers[c->ptr](inf, p);
    }
    if (!inside) inf->inputs.can_interact = 0;
    return 1;
}
