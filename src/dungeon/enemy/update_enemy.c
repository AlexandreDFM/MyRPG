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

sfIntRect move_in_room(sfIntRect r, player *p, player *e, wininf *inf)
{
    sfVector2i target = (sfVector2i){r.width, r.height};
    map_inf *mi = inf->dungeon.inf;
    sfVector2i nextp = global_to_local(p->nextpos);
    sfVector2f ppos = sfSprite_getPosition(p->test);
    if (r.left == r.top) target = global_to_local(ppos);
    else target = get_closest_exit(r.top, ppos, mi);
    sfVector2f targetf = (sfVector2f){target.x, target.y};
    sfIntRect final = (sfIntRect){r.width, r.height, r.width, r.height};
    sfVector2f oldprevpos = e->sentpos; float maxdst = 1000.0f;
    e->sentpos = (sfVector2f){(float)final.width, (float)final.height};
    for (int y = -1; y < 2; y++)
        maxdst = get_neighbours_enemy(y, targetf, maxdst, &final);
    if (final.width == nextp.x && final.height == nextp.y)
        return (sfIntRect){-1, -1, -1, -1};
    int count = is_valid_move(inf, (sfVector2i){final.width, final.height}, 1);
    if (count) {
        e->sentpos = oldprevpos;
        return (sfIntRect){-1, -1, -1, -1};
    } return final;
}

void update_enemy(player *e, wininf *inf, player *p)
{
    map_inf *mi = inf->dungeon.inf;
    sfIntRect final;
    sfVector2f ppos = sfSprite_getPosition(p->test);
    sfVector2f epos = sfSprite_getPosition(e->test);
    sfVector2i elpos = global_to_local(epos);
    sfVector2i plpos = global_to_local(ppos);
    int proom = get_current_room(ppos, mi), eroom = get_current_room(epos, mi);
    sfIntRect rect = (sfIntRect){proom, eroom, elpos.x, elpos.y};
    int old = get_current_roomlo((sfVector2i){e->sentpos.x, e->sentpos.y}, mi);
    int enemycond = (mi->map[elpos.y][elpos.x] == 'E' && old != -1);
    if (enemycond || eroom == -1) {
        move_in_tunnel(e, inf, p); return;
    } else {
        final = move_in_room(rect, p, e, inf);
        printf("%d %d %d %d\n", final.left, final.top, final.width, final.height);
        if (final.left == -1) return;
        if (final.width == plpos.x && final.height == plpos.y) return;
        e->target = local_to_global(final.width, final.height);
        e->vel = (sfVector2f){e->target.x - epos.x, e->target.y - epos.y};
    }
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

void scan_neighb(player *e, map_inf *mi, sfIntRect pi, sfFloatRect *myf)
{
    for (int x = pi.width - 1; x < pi.width + 2; x++) {
        sfVector2i lp = (sfVector2i){x, myf->top};
        char c = mi->map[(int)myf->top][x];
        if (c != 'E' && c != ' ') continue;
        sfVector2f slp = (sfVector2f){lp.x, lp.y};
        float dst = distance((sfVector2f){pi.left, pi.top},
            slp);
        int isold = lp.x == (int)e->sentpos.x && lp.y == (int)e->sentpos.y;
        int count = get_current_roomlo(lp, mi);
        int cond = count == -1 || c == 'E';
        if (myf->left > dst && c != '.' && cond && !isold) {
            myf->left = dst;
            myf->width = lp.x; myf->height = lp.y;
        }
    }
}

sfVector2i check_neighb(sfVector2i i, map_inf *mi, player *e, sfVector2i plpos)
{
    sfFloatRect myf = (sfFloatRect){1000, 1000, i.x, i.y};
    for (int y = i.y - 1; y < i.y + 2; y++) {
        myf.top = y;
        scan_neighb(e, mi, (sfIntRect){plpos.x, plpos.y, i.x, i.y}, &myf);
    }
    return (sfVector2i){(int)myf.width, (int)myf.height};
}

void move_in_tunnel(player *e, wininf *inf, player *p)
{
    map_inf *mi = inf->dungeon.inf;
    sfVector2f epos = sfSprite_getPosition(e->test);
    sfVector2i plpos = global_to_local(sfSprite_getPosition(p->test));
    sfVector2i i = global_to_local(epos);
    sfVector2f oldprevpos = e->sentpos;
    e->sentpos = (sfVector2f){i.x, i.y};
    sfVector2i final = check_neighb(i, mi, e, plpos);
    sfVector2f ffinal = local_to_global(final.x, final.y);
    int count = is_valid_move(inf, (sfVector2i){final.x, final.y}, 1);
    if (count) {
        e->sentpos = oldprevpos;
        return;
    }
    e->vel = (sfVector2f){ffinal.x - epos.x, ffinal.y - epos.y};
    e->target = ffinal;
}

void update_mobs(wininf *inf, player *p)
{
    for (list *t = inf->dungeon.enemies; t; t = t->next) {
        player *enemy = t->data;
        update_enemy(enemy, inf, p);
    }
}
