/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** player_movement
*/

#include "rpg.h"

void draw_player(wininf *inf, player *p)
{
    if (!inf->dungeon.in) {
        p->vel = inf->inputs.axis;
        perform_free_movement(inf, p);
    } else {
        p->vel = inf->inputs.axis;
        perform_dungeon_movement(inf, p);
    }
    if (inf->net->other.p.test) {
        sfVector2f pos = sfSprite_getPosition(inf->net->other.p.test);
        // pos = my_lerp(pos, inf->net->other.target, inf->time.dt * 40.0f);
        // sfSprite_setPosition(inf->net->other.p.test, pos);
        if (inf->net->other.cscene == inf->c_scene)
            sfRenderWindow_drawSprite(inf->win, inf->net->other.p.test, 0);
    }
    update_camera(inf);
    sfRenderWindow_drawSprite(inf->win, p->test, 0);
}

void perform_free_movement(wininf *inf, player *p)
{
    sfVector2f po = sfSprite_getPosition(p->test);
    sfVector2f nextp = (sfVector2f){po.x, po.y};
    list *cols = inf->scenes[inf->c_scene].colls;
    if (inf->c_scene != DUNGEON)
        if (!(is_valid(cols, nextp, &p->vel, inf, p) && !inf->transition))
            return;
    nextp.x += p->vel.x; nextp.y += p->vel.y;
    sfVector2f np = my_lerp(po, nextp, p->speed * inf->time.dt);
    sfSprite_setPosition(p->test, np);
    if (!is_same(po, nextp, 0.1f) && inf->net->is_multi) {
        add_ord(POSITION, &np, sizeof(sfVector2f), inf->net->packet);
    }
}

void perform_dungeon_movement(wininf *inf, player *p)
{
    sfVector2f pos = sfSprite_getPosition(p->test);
    sfVector2f axis = inf->inputs.axis;
    sfVector2f input = (sfVector2f){pos.x + axis.x * 24.0f,
        axis.y * 24.0f + pos.y};
    sfVector2i np = global_to_local(input);
    sfVector2i target = global_to_local(p->nextpos);
    int cond = is_same(axis, (sfVector2f){0.0f, 0.0f}, 0.3f);
    int cond2 = is_same(pos, p->nextpos, 2.0f);
    if (inf->dungeon.inf->map[np.y][np.x] == ' ' && !cond && cond2 && (np.x != target.x || np.y != target.y)) {
        p->nextpos = local_to_global(np.x, np.y);
        p->time = 0.0f;
    }
    p->time += (inf->time.dt * 4.0f);
    sfVector2f newp = my_lerp(pos, p->nextpos, p->time / 100.0f);
    sfSprite_setPosition(p->test, newp);
}
