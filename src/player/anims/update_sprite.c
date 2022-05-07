/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** update_sprite
*/

#include "rpg.h"

int direction_play_iddle(int d)
{
    if (d == PDOWNRIGHT || d == PDOWNRIGHTIDDLE)
        return d == PDOWNRIGHTIDDLE ? - 1 : PDOWNRIGHTIDDLE;
    if (d == PUPRIGHT || d == PUPRIGHTIDDLE)
        return d == PUPRIGHTIDDLE ? -1 : PUPRIGHTIDDLE;
    if (d == PDOWNLEFT || d == PDOWNLEFTIDDLE)
        return d == PDOWNLEFTIDDLE ? -1 : PDOWNLEFTIDDLE;
    if (d == PUPLEFT || d == PUPLEFTIDDLE)
        return d ==  PUPLEFTIDDLE ? -1 : PUPLEFTIDDLE;
    if (d == PUPRIGHT || d == PUPRIGHTIDDLE)
        return d == PUPRIGHTIDDLE ? -1 : PUPRIGHTIDDLE;
    if (d == PRIGHT || d == PRIGHTIDDLE)
        return d == PRIGHTIDDLE ? -1 : PRIGHTIDDLE;
    if (d == PLEFT || d == PLEFTIDDLE)
        return d == PLEFTIDDLE ? -1 : PLEFTIDDLE;
    if (d == PDOWN || d == PDOWNIDDLE)
        return d == PDOWNIDDLE ? -1 : PDOWNIDDLE;
    if (d == PUP || d == PUPIDDLE) return d == PUPIDDLE ? -1 : PUPIDDLE;
    return 84;
}

int direction_play(wininf *inf, player *p)
{
    float axis_x = p->vel.x; float axis_y = p->vel.y; int d = p->direction;
    if (axis_x > 0.5f && axis_y > 0.5f)
        return d == PDOWNRIGHT ? -1 : PDOWNRIGHT;
    if (axis_x > 0.5f && axis_y < -0.5f)
        return d == PUPRIGHT ? -1 : PUPRIGHT;
    if (axis_x < -0.5f && axis_y > 0.5f)
        return d == PDOWNLEFT ? -1 : PDOWNLEFT;
    if (axis_x < -0.5f && axis_y < -0.5f)
        return d == PUPLEFT ? -1 : PUPLEFT;
    if (axis_x > 0.5f) return d == PRIGHT ? -1 : PRIGHT;
    if (axis_x < -0.5f) return d == PLEFT ? -1 : PLEFT;
    if (axis_y > 0.5f) return d == PDOWN ? -1 : PDOWN;
    if (axis_y < -0.5f) return d == PUP ? -1 : PUP;
    if (axis_x == 0.0f && axis_y == 0.0f && direction_play_iddle(d) != 84) {
        return direction_play_iddle(d);
    }
    return d == PNONE_DIRECTION ? -1 : PNONE_DIRECTION;
}

void change_anim(player *p, int n, float mirror)
{
    int random = 0, random1 = 0;
    p->r = (sfIntRect) {p->offset * p->rlist[n][0], 0,
    p->slist[3], p->slist[4]};
    p->limit = (sfVector2i) {p->offset * p->rlist[n][0],
    p->offset * p->rlist[n][1]};
    if ((p->rlist[n][1] - p->rlist[n][0]) == 0) {
        p->r.left -= p->offset;
    } else {
        random = (rand() % (p->rlist[n][1] - p->rlist[n][0]));
        random1 = random <= 0 ? 0 : random;
        p->r.left += p->offset * random1;
    }
    sfSprite_setTextureRect(p->test, p->r);
    sfSprite_setScale(p->test, (sfVector2f) {mirror, 1.0f});
}

void player_manage_animation_changement(int d, player *p)
{
    if (d == PDOWNRIGHT) change_anim(p, 1, -1.0f);
    if (d == PDOWNLEFT) change_anim(p, 1, 1.0f);
    if (d == PUPLEFT) change_anim(p, 3, 1.0f);
    if (d == PUPRIGHT) change_anim(p, 3, -1.0f);
    if (d == PLEFT) change_anim(p, 2, 1.0f);
    if (d == PRIGHT) change_anim(p, 2, -1.0f);
    if (d == PUP) change_anim(p, 4, 1.0f);
    if (d == PDOWN) change_anim(p, 0, 1.0f);
    if (d == PDOWNRIGHTIDDLE) change_anim(p, 6, -1.0f);
    if (d == PDOWNLEFTIDDLE) change_anim(p, 6, 1.0f);
    if (d == PUPLEFTIDDLE) change_anim(p, 8, 1.0f);
    if (d == PUPRIGHTIDDLE) change_anim(p, 8, -1.0f);
    if (d == PRIGHTIDDLE) change_anim(p, 7, -1.0f);
    if (d == PLEFTIDDLE) change_anim(p, 7, 1.0f);
    if (d == PUPIDDLE) change_anim(p, 9, 1.0f);
    if (d == PDOWNIDDLE) change_anim(p, 5, 1.0f);
}

void player_direction_management(wininf *inf, player *p)
{
    if (p->limit.x == p->limit.y) {
    } else if (p->animc > 0.30f) {
        p->r = move_rect_player(*p);
        p->animc = 0.0f;
    }
    p->animc += inf->time.dt;
    if (inf->c_menu != NONE) return;
    int d = direction_play(inf, p); if (d == -1) return;
    p->direction = d;
    player_manage_animation_changement(d, p);
}
