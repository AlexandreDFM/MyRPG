/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** main_menu_play_options
*/

#include "rpg.h"

void play(wininf *inf)
{
    inf->current_menu = inf->load_menu;
    inf->c_menu = LOAD_SAVE;
    inf->main_menu->focus = 0;
    inf->load_menu->focus = 1;
}

void options(wininf *inf)
{
    inf->current_menu->focus = 0;
    inf->current_menu = inf->options_menu;
    inf->c_menu = OPTIONS;
    inf->main_menu->focus = 0;
    inf->options_menu->focus = 1;
}
