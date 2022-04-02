/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** draw_home
*/

#include "rpg.h"

void draw_home(wininf *inf)
{
    draw_list(inf->scenes[0].statics, inf->win);
    draw_entity(&inf->time, inf->scenes[0].animated, inf->win);
}
