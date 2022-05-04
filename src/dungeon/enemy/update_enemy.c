/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_enemy
*/

#include "rpg.h"

float get_neighbours_enemy(int y, sfVector2f target, float mdst, sfIntRect *p)
{
    for (int x = -1; x < 2; x++) {
        sfVector2f v = (sfVector2f){x + p->left, y + p->top};
        float dst = distance(target, v);
        if (dst < mdst) {
            mdst = dst;
            p->width = x + p->left;
            p->height = y + p->top;
        }
    }
    return mdst;
}

void update_enemy(player *e, wininf *inf, player *p)
{
    map_inf *mi = inf->dungeon.inf;
    sfVector2f ppos = sfSprite_getPosition(p->test);
    sfVector2f epos = sfSprite_getPosition(e->test);
    sfVector2i elpos = global_to_local(epos);
    sfVector2i plpos = global_to_local(ppos);
    sfVector2i target = elpos;
    int proom = get_current_room(ppos, mi);
    int eroom = get_current_room(epos, mi);
    int enemycond = mi->map[elpos.y][elpos.x] == 'E' || eroom == -1;
    if (proom == -1 || enemycond) {
        move_in_tunnel(e, inf, p);
        return;
    }
    if (proom == eroom)
        target = global_to_local(ppos);
    else
        target = get_closest_exit(eroom, ppos, mi);
    sfVector2f targetf = (sfVector2f){target.x, target.y};
    sfIntRect final = (sfIntRect){elpos.x, elpos.y, elpos.x, elpos.y};
    float maxdst = 1000;
    for (int y = -1; y < 2; y++) {
        maxdst = get_neighbours_enemy(y, targetf, maxdst, &final);
    }
    if (final.width == plpos.x && final.height == plpos.y) return;
    sfVector2f vec = local_to_global(final.width, final.height);
    sfSprite_setPosition(e->test, vec);
}

float scanx_tunnel(int y, sfVector2f target, float mdst, sfIntRect *p)
{
    for (int x = -1; x < 2; x++) {
        sfVector2f v = (sfVector2f){x + p->left, y + p->top};
        float dst = distance(target, v);
        if (dst < mdst) {
            mdst = dst;
            p->width = x + p->left;
            p->height = y + p->top;
        }
    }
    return mdst;
}

void move_in_tunnel(player *e, wininf *inf, player *p)
{
    map_inf *mi = inf->dungeon.inf;
    sfVector2i plpos = global_to_local(sfSprite_getPosition(p->test));
    sfVector2i i = global_to_local(sfSprite_getPosition(e->test));
    float maxdst = 1000.0f;
    sfVector2i final = (sfVector2i){i.x, i.y};
    for (int y = i.y - 1; y < i.y + 2; y++) {
        for (int x = i.x - 1; x < i.x + 2; x++) {
            sfVector2i lp = (sfVector2i){x, y};
            if (mi->map[y][x] != 'E' && mi->map[y][x] != ' ')
                continue;
            sfVector2f slp = (sfVector2f){lp.x, lp.y};
            float dst = distance((sfVector2f){plpos.x, plpos.y},
                slp);
            char c = mi->map[lp.y][lp.x];
            int isold = lp.x == (int)e->sentpos.x && lp.y == (int)e->sentpos.y;
            int cond = get_current_room(slp, mi) == -1;
            if (maxdst > dst && c != '.' && cond && !isold) {
                maxdst = dst;
                final.x = lp.x; final.y = lp.y;
            }
        }
    }
    sfVector2f ffinal = local_to_global(final.x, final.y);
    if (final.x != i.x && final.y != i.y)
        e->sentpos = (sfVector2f){final.x, final.y};
    sfSprite_setPosition(e->test, ffinal);
}

void update_mobs(wininf *inf, player *p)
{
    for (list *t = inf->dungeon.enemies; t; t = t->next) {
        player *enemy = t->data;
        update_enemy(enemy, inf, p);
    }
}
