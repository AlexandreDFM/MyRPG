/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** options_pointers
*/

#include "rpg.h"

void change_keybind(wininf *inf)
{
    inf->options_menu->focus = 0;
    inf->waiting_key = 1;
    inf->key_change = ((choices *)inf->options_menu->selected->data)->ptr;
    sfText *tmp = ((choices *)inf->options_menu->selected->data)->choice;
    sfVector2f pos = sfText_getPosition(tmp);
    pos.y += 20;
    sfText_setString(tmp, "-"); sfText_setPosition(tmp, pos);
}

void go_back(wininf *inf)
{
    inf->current_menu->selected = inf->current_menu->head;
    inf->current_menu->focus = 0;
    inf->main_menu->focus = 1;
    inf->current_menu = inf->main_menu;
    inf->c_menu = NONE;
}
