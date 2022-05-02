/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** handle_transitions
*/

#include "rpg.h"

void update_transition(wininf *inf, player p)
{
    sfColor col = sfRectangleShape_getFillColor(inf->transi);
    float new_a = inf->ftransi;
    if (inf->transition == 1) {
        if (new_a > 0.99f) {
            inf->transition = -1; inf->time.transi = 0.0f;
            if (!inf->change_scene) return;
            inf->c_scene = inf->next_scene;
            sfSprite_setPosition(p.test, inf->next_pos);
            col.a = (int)(new_a * 255.0f);
            sfRectangleShape_setFillColor(inf->transi, col);
            return;
        }
        new_a += inf->time.dt * 3.0f;
    } else {
        if (new_a <= inf->time.dt) {
            inf->transition = 0; inf->time.transi = 0.0f;
        }
        new_a -= inf->time.dt * 3.0f;
    }
    col.a = (int)(new_a * 255.0f);
    inf->ftransi = new_a;
    sfRectangleShape_setFillColor(inf->transi, col);
}
