/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** others_pointers
*/

#include "rpg.h"

void go_ig_options(wininf *inf)
{
    inf->current_menu->focus = 0;
    inf->current_menu = inf->ig_options_menu;
    inf->c_menu = IG_OPTIONS;
    inf->ig_options_menu->focus = 1;
}

void dummy(wininf *inf)
{
    return;
}
