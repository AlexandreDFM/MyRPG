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
        if (inf->c_menu == NONE)
            perform_free_movement(inf, p);
    } else {
        p->vel = inf->inputs.axis;
        perform_dungeon_movement(inf, p);
    }
    if (inf->net->is_multi && inf->net->other.p) {
        // sfVector2f pos = sfSprite_getPosition(inf->net->other.p->test);
        // pos = my_lerp(pos, inf->net->other.target, inf->time.dt * 40.0f);
        // sfSprite_setPosition(inf->net->other.p->test, pos);
        if (inf->net->other.cscene == inf->c_scene)
            sfRenderWindow_drawSprite(inf->win, inf->net->other.p->test, 0);
    } update_camera(inf);
    sfShader_setFloatUniform((sfShader*)inf->state.shader, "time",
    inf->time.time);
    sfRenderWindow_drawSprite(inf->win, p->test, p->shiny ? &inf->state : 0);
}

void perform_free_movement(wininf *inf, player *p)
{
    sfVector2f po = sfSprite_getPosition(p->test);
    sfVector2f nextp = (sfVector2f){po.x, po.y};
    list *cols = inf->scenes[inf->c_scene].colls;
    nextp.x += p->vel.x; nextp.y += p->vel.y;
    sfVector2f np = my_lerp(po, nextp, p->speed * inf->time.dt);
    sfFloatRect rect = (sfFloatRect){np.x, np.y, p->vel.x, p->vel.y};
    if (inf->c_scene != DUNGEON)
        if (!(is_valid(cols, &rect, inf, p) && !inf->transition))
            return;
    sfSprite_setPosition(p->test, np);
    if (!is_same(np, p->sentpos, 1.0f) && inf->net->is_multi) {
        network *net = inf->net;
        p->sentpos = np;
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
    char c = inf->dungeon.inf->map[np.y][np.x];
    int walkable = c == ' ' || c == 'E';
    if (walkable && !cond && cond2 && (np.x != target.x || np.y != target.y)) {
        p->nextpos = local_to_global(np.x, np.y);
        p->time = 0.0f;
        update_mobs(inf, p);
    }
    sfVector2f newp = my_lerp(pos, p->nextpos, inf->time.dt * 4.0f);
    sfSprite_setPosition(p->test, newp);
}
