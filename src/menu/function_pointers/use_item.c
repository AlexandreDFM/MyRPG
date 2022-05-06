/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** use_item
*/

#include "rpg.h"

void go_use_item(wininf *inf)
{
    inf->current_menu->focus = 0;
    inf->current_menu->selected = inf->current_menu->head;
    inf->current_menu = inf->use_item_menu;
    inf->c_menu = USE_ITEM;
    inf->current_menu->focus = 1;
    inf->use_item_menu->press = inf->pressed;
}
