/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** scan_surroundings
*/

#include "rpg.h"

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
        int count = get_current_roomlo(lp, mi);
        int cond = count == -1 || mi->map[lp.y][lp.x] == 'E';
        if (myf->left > dst && c != '.' && cond) {
            myf->left = dst;
            myf->width = lp.x; myf->height = lp.y;
        }
    }
}

sfVector2i check_neighb(sfVector2i i, map_inf *mi, player *e, sfVector2i pl)
{
    sfFloatRect myf = (sfFloatRect){1000, 1000, i.x, i.y};
    for (int y = i.y - 1; y < i.y + 2; y++) {
        myf.top = y;
        scan_neighb(e, mi, (sfIntRect){pl.x, pl.y, i.x, i.y}, &myf);
    }
    return (sfVector2i){(int)myf.width, (int)myf.height};
}
