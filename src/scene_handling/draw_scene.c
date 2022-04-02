/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** draw_home
*/

#include "rpg.h"

void draw_static_scene(wininf *inf, scene s)
{
    draw_list(s.statics, inf->win);
    draw_entity(&inf->time, s.animated, inf->win);
}
