/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** load_menu_pointers
*/

#include "rpg.h"

void yes_but(wininf *inf)
{
    inf->c_scene = HOME;
    inf->c_menu = NONE;
}

void no_but(wininf *inf)
{
    inf->current_menu = inf->main_menu;
    inf->c_menu = NONE;
}
