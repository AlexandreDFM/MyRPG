/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** player_movement
*/

#include "rpg.h"

void draw_player(wininf *inf, player p)
{
    p.vel = inf->inputs.axis;
    sfVector2f po = sfSprite_getPosition(p.test);
    sfVector2f nextp = (sfVector2f){po.x, po.y};
    list *cols = inf->scenes[inf->c_scene].colls;
    if (check_if_valid_movement(cols, nextp, &p.vel, inf) && !inf->transition) {
        nextp.x += p.vel.x; nextp.y += p.vel.y;
        sfVector2f np = my_lerp(po, nextp, p.speed * inf->time.dt);
        sfSprite_setPosition(p.test, np);
    }
    update_camera(inf->camera, inf->time.dt, inf->win, inf->transition_rect);
    sfRenderWindow_drawSprite(inf->win, p.test, 0);
}
