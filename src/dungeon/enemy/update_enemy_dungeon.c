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
