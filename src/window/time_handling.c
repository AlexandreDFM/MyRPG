/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** time_handling
*/

#include "rpg.h"

void init_times(wininf *infos)
{
    infos->time.dt_cal = my_clock();
    infos->time.anim = 0.0f;
    infos->time.dt = 0.0f;
    infos->time.transi = 0.0f;
    infos->time.time = 0.0f;
    infos->time.intro_anim = 0.0f;
    infos->time.intro_anim2 = 0.0f;
    infos->time.ditto_anim = 0.0f;
    infos->time.ditto_anim2 = 0.0f;
}

void update_time(wininf *infos)
{
    float dt = sfTime_asSeconds(sfClock_restart(infos->time.dt_cal));
    if (infos->time.anim > RATE) {
        infos->time.anim = 0.0f;
    }
    infos->time.intro_anim += dt;
    infos->time.intro_anim2 += dt;
    infos->time.ditto_anim += dt;
    infos->time.ditto_anim2 += dt;
    infos->time.time += dt;
    infos->time.anim += dt;
    infos->time.dt = dt;
}
