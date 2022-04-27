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
    perform_free_movement(inf, p);
    update_camera(inf->camera, inf->time.dt, inf->win, inf->transi);
    if (inf->net->other.p.test) {
        sfVector2f pos = sfSprite_getPosition(inf->net->other.p.test);
        // pos = my_lerp(pos, inf->net->other.target, inf->time.dt * 40.0f);
        // sfSprite_setPosition(inf->net->other.p.test, pos);
        if (inf->net->other.cscene == inf->c_scene)
            sfRenderWindow_drawSprite(inf->win, inf->net->other.p.test, 0);
    }
    sfRenderWindow_drawSprite(inf->win, p.test, 0);
}

void perform_free_movement(wininf *inf, player p)
{
    sfVector2f po = sfSprite_getPosition(p.test);
    sfVector2f nextp = (sfVector2f){po.x, po.y};
    list *cols = inf->scenes[inf->c_scene].colls;
    if (inf->c_scene != DUNGEON)
        if (!(is_valid(cols, nextp, &p.vel, inf, p) && !inf->transition))
            return;
    nextp.x += p.vel.x; nextp.y += p.vel.y;
    sfVector2f np = my_lerp(po, nextp, p.speed * inf->time.dt);
    sfSprite_setPosition(p.test, np);
    if (!is_same(po, nextp, 0.1f) && inf->net->is_multi) {
        add_ord(POSITION, &np, sizeof(sfVector2f), inf->net->packet);
    }
}
