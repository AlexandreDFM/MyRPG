/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** options_pointers
*/

#include "rpg.h"

void go_main(wininf *inf)
{
    inf->current_menu->selected = inf->current_menu->head;
    inf->current_menu->focus = 0;
    inf->main_menu->focus = 1;
    inf->current_menu = inf->main_menu;
    inf->c_menu = NONE;
}

void go_others(wininf *inf)
{
    inf->current_menu->focus = 0;
    inf->current_menu->selected = inf->current_menu->head;
    inf->current_menu = inf->others_menu;
    inf->c_menu = OTHERS;
    inf->current_menu->focus = 1;
    inf->others_menu->press = inf->pressed;
}

void go_pause(wininf *inf)
{
    inf->current_menu->focus = 0;
    inf->current_menu->selected = inf->current_menu->head;
    inf->current_menu = inf->pause_menu;
    inf->c_menu = PAUSE;
    inf->pause_menu->focus = 1;
    inf->pause_menu->press = inf->pressed;
}