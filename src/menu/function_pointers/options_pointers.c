/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** options_pointers
*/

#include "rpg.h"

void change_volume(wininf *inf)
{
    if (inf->event.type == sfEvtKeyPressed && inf->event.key.code ==
    inf->inputs.keys.mright && inf->pressed == 0) {
        inf->pressed = 1;
        right_main_vol(inf);
        right_main_fps(inf);
    }
    if (inf->event.type == sfEvtKeyPressed && inf->event.key.code ==
    inf->inputs.keys.mleft && inf->pressed == 0) {
        inf->pressed = 1;
        left_main_vol(inf);
        left_main_fps(inf);
    }
}

void change_keybind(wininf *inf)
{
    inf->options_menu->focus = 0;
    inf->waiting_key = 1;
    inf->current_menu = inf->change_keys_menu;
    inf->key_change = ((choices *)inf->current_menu->selected->data)->ptr;
    sfText *tmp = ((choices *)inf->current_menu->selected->data)->choice;
    sfVector2f pos = sfText_getPosition(tmp);
    pos.y += 20;
    sfText_setString(tmp, "-"); sfText_setPosition(tmp, pos);
}
