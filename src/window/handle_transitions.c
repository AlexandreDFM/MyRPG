/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** handle_transitions
*/

#include "rpg.h"

void apply_transition(float new_a, int timecond, wininf *inf, player *p)
{
    if (new_a > 0.99f && (timecond || !inf->dungeon.in)) {
        inf->transition = -1; inf->time.transi = 0.0f;
        if (inf->change_scene != 1) reroll_dungeon(inf, p); return;
        inf->transition = -1;
        inf->c_scene = inf->next_scene;
        sfSprite_setPosition(p->test, inf->next_pos);
        return 1;
    }
    return 0;
}

void update_transition(wininf *inf, player *p)
{
    sfColor col = sfRectangleShape_getFillColor(inf->transi);
    float new_a = inf->ftransi;
    if (inf->transition == 1) {
        int timecond = inf->dungeon.time > 7.0f || !inf->dungeon.ended;
        if (apply_transition(new_a, timecond, inf, p)) return;
        new_a += inf->time.dt * 3.0f;
    } else {
        if (new_a <= inf->time.dt) {
            inf->transition = 0; inf->time.transi = 0.0f;
        } new_a -= inf->time.dt * 3.0f;
    } new_a = new_a >= 1.0f ? 1.0f : new_a < 0.0f ? 0.0f : new_a;
    col.a = (int)(new_a * 255.0f);
    inf->ftransi = new_a;
    sfRectangleShape_setFillColor(inf->transi, col);
}
