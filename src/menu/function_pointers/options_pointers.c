/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** options_pointers
*/

#include "rpg.h"

int change_keybind(wininf *inf, int key_change)
{
    inf->options_menu->focus = 0;
    inf->waiting_key = 1;
    inf->key_change = key_change;
    float blink = 0.0f; int interacting = 0;
    sfText *tmp = ((choices *)inf->options_menu->selected->data)->choice;
    sfVector2f pos = sfText_getPosition(tmp);
    pos.y += 20;
    sfText_setString(tmp, "-"); sfText_setPosition(tmp, pos);
}

void key_up(wininf *inf)
{
    change_keybind(inf, 0);
}

void key_down(wininf *inf)
{
    change_keybind(inf, 1);
}

void key_left(wininf *inf)
{
    change_keybind(inf, 2);
}

void key_right(wininf *inf)
{
    change_keybind(inf, 3);
}

void key_interact(wininf *inf)
{
    change_keybind(inf, 4);
}

void key_inventory(wininf *inf)
{
    change_keybind(inf, 5);
}

void key_attack(wininf *inf)
{
    change_keybind(inf, 6);
}

void key_back(wininf *inf)
{
    change_keybind(inf, 7);
}

void go_back(wininf *inf)
{
    inf->options_menu->focus = 0;
    inf->main_menu->focus = 1;
    inf->current_menu = inf->main_menu;
    inf->c_menu = NONE;
}
