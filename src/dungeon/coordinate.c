/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** coordinate
*/

#include "rpg.h"
#include "dungeon.h"

sfVector2f get_random_position(sfIntRect **rooms, int count)
{
    int rdm = (rand() % (count - 1));
    sfIntRect *r = rooms[rdm];
    sfVector2f start_posf  = (sfVector2f){r->left + rand() % (r->width - 1),
        r->top + rand() % (r->height - 1)};
    return local_to_global((int)start_posf.x, (int)start_posf.y);
}

int get_current_roomlo(sfVector2i pos, map_inf *inf)
{
    for (int i = 0; inf->rooms[i]; i++) {
        sfIntRect *rect = inf->rooms[i];
        if (sfIntRect_contains(rect, pos.x, pos.y)) {
            return i;
        }
    }
    return -1;
}

int get_current_room(sfVector2f pos, map_inf *inf)
{
    sfVector2i lpos = global_to_local(pos);
    return get_current_roomlo(lpos, inf);
}

void get_closest_exitx(sfIntRect cr, map_inf *i, sfVector2f *dy, sfIntRect *e)
{
    for (int x = cr.left; x < cr.left + cr.width; x++) {
        if (i->map[(int)dy->y][x] != 'E') continue;
        sfVector2f exi = (sfVector2f){x, dy->y};
        float nds = distance(exi, (sfVector2f){e->width, e->height});
        if (dy->x > nds) {
            dy->x = nds;
            sfVector2i nd = (sfVector2i){x, dy->y};
            e->left = nd.x;
            e->top = nd.y;
        }
    }
}

sfVector2i get_closest_exit(int r, sfVector2f t, map_inf *inf)
{
    if (r == -1) return (sfVector2i){0, 0};
    sfIntRect croom = *(inf->rooms[r]);
    sfVector2f dsty = (sfVector2f){MAP_SIZE * 2, 0};
    sfVector2i lt = global_to_local(t);
    sfIntRect endplt = (sfIntRect){0, 0, lt.x, lt.y};
    for (int y = croom.top; y < croom.top + croom.height + 1; y++) {
        dsty.y = (float)y;
        get_closest_exitx(croom, inf, &dsty, &endplt);
    }
    return (sfVector2i){endplt.left, endplt.top};
}
