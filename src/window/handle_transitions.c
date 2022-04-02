/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** handle_transitions
*/

#include "rpg.h"

void update_transition(wininf *inf, player p)
{
    sfColor col = sfRectangleShape_getFillColor(inf->transition_rect); 
    float new_a = col.a / 255.0f;
    if (inf->transition == 1) {
        if (new_a > 0.99f) {
            inf->transition = -1;
            inf->time.transi = 0.0f;
            if (!inf->change_scene) return;
            inf->c_scene = inf->next_scene;
            sfSprite_setPosition(p.test, inf->next_pos);
        }
        inf->time.transi += inf->time.dt / 15.0f;
        new_a = my_lerpf(new_a, 1.0f, 9.0 * inf->time.transi);
    } else {
        if (new_a <= 0.05f) {
            inf->transition = 0;
            inf->time.transi = 0.0f;
        }
        inf->time.transi += inf->time.dt / 15.0f;
        new_a = my_lerpf(new_a, 0.0f, 9.0 * inf->time.transi);
    }
    col.a = (int)(new_a * 255.0f);
    sfRectangleShape_setFillColor(inf->transition_rect, col);
}