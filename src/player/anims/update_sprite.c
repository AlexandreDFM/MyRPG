/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** update_sprite
*/

#include "rpg.h"

int direction_play(wininf *inf, player *p)
{
    int axis_x = p->vel.x; int axis_y = p->vel.y;
    int d = p->direction;
    if (axis_x > 0.5 && axis_y > 0.5) return d == PDOWNRIGHT ? -1 : PDOWNRIGHT;
    if (axis_x > 0.5 && axis_y < -0.5) return d == PUPRIGHT ? -1 : PUPRIGHT;
    if (axis_x < -0.5 && axis_y > 0.5) return d == PDOWNLEFT ? -1 : PDOWNLEFT;
    if (axis_x < -0.5 && axis_y < -0.5) return d == PUPLEFT ? -1 : PUPLEFT;
    if (axis_x > 0.5) return d == PRIGHT ? -1 : PRIGHT;
    if (axis_x < -0.5) return d == PLEFT ? -1 : PLEFT;
    if (axis_y > 0.5) return d == PDOWN ? -1 : PDOWN;
    if (axis_y < -0.5) return d == PUP ? -1 : PUP;
    return d == PNONE_DIRECTION ? -1 : PNONE_DIRECTION;
}

void change_anim(player *p, int n, float mirror)
{
    p->r = (sfIntRect) {p->offset * p->rlist[n][0], 0,
    p->slist[3], p->slist[4]};
    p->limit = (sfVector2i) {p->offset * p->rlist[n][0],
    p->offset * p->rlist[n][1]};
    sfSprite_setTextureRect(p->test, p->r);
    sfSprite_setScale(p->test, (sfVector2f) {mirror, 1.0f});
}

void player_direction_management(wininf *inf, player *p)
{
    if (p->animc > 0.30f) {
        p->r = move_rect_player(*p);
        p->animc = 0.0f;
    }
    p->animc += inf->time.dt;
    int d = direction_play(inf, p); if (d == -1) return;
    p->direction = d;
    if (d == PDOWNRIGHT) change_anim(p, 1, -1.0f);
    if (d == PDOWNLEFT) change_anim(p, 1, 1.0f);
    if (d == PUPLEFT) change_anim(p, 3, 1.0f);
    if (d == PUPRIGHT) change_anim(p, 3, -1.0f);
    if (d == PLEFT) change_anim(p, 2, 1.0f);
    if (d == PRIGHT) change_anim(p, 2, -1.0f);
    if (d == PUP) change_anim(p, 4, 1.0f);
    if (d == PDOWN) change_anim(p, 0, 1.0f);
    // if (d == PNONE_DIRECTION) change_anim(p, 5, 1.0f);
}
