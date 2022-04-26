/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** load_menu_pointers
*/

#include "rpg.h"

void yes_but(wininf *inf)
{
    inf->main_menu->focus = 1;
    inf->load_menu->focus = 0;
    inf->c_scene = HOME;
    inf->c_menu = NONE;
    inf->current_menu = NULL;
}

void no_but(wininf *inf)
{
    sfSprite_setPosition(inf->load_menu->cursor, inf->load_menu->base_pos);
    inf->c_menu = NONE;
    inf->main_menu->focus = 1;
    inf->load_menu->focus = 0;
    inf->current_menu = inf->main_menu;
}
