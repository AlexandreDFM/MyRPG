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
        if (((choices *)inf->current_menu->selected->data)->ptr == 0) {
            inf->vol_sound += inf->vol_sound < 100 ? 5 : 0;
            sfText_setString(
                ((choices *)inf->current_menu->selected->data)->choice,
                my_itoa(inf->vol_sound));
        } if (((choices *)inf->current_menu->selected->data)->ptr == 1) {
            inf->vol_music += inf->vol_music < 100 ? 5 : 0;
            sfText_setString(
                ((choices *)inf->current_menu->selected->data)->choice,
                my_itoa(inf->vol_music));
        } if (((choices *)inf->current_menu->selected->data)->ptr == 2) {
            inf->settings->c_fps += inf->settings->c_fps < 5 ? 1 : 0;
            sfText_setString(
                ((choices *)inf->current_menu->selected->data)->choice,
                inf->settings->fps[inf->settings->c_fps]);
                sfRenderWindow_setFramerateLimit(inf->win, inf->settings->c_fps
                < 5 ? my_atoi(inf->settings->fps[inf->settings->c_fps]) : 0);
        }
    }
    if (inf->event.type == sfEvtKeyPressed && inf->event.key.code ==
    inf->inputs.keys.mleft && inf->pressed == 0) {
        inf->pressed = 1;
        if (((choices *)inf->current_menu->selected->data)->ptr == 0) {
            inf->vol_sound -= inf->vol_sound > 0 ? 5 : 0;
            sfText_setString(
                ((choices *)inf->current_menu->selected->data)->choice,
                my_itoa(inf->vol_sound));
        } if (((choices *)inf->current_menu->selected->data)->ptr == 1) {
            inf->vol_music -= inf->vol_music > 0 ? 5 : 0;
            sfText_setString(
                ((choices *)inf->current_menu->selected->data)->choice,
                my_itoa(inf->vol_music));
        } if (((choices *)inf->current_menu->selected->data)->ptr == 2) {
            inf->settings->c_fps -= inf->settings->c_fps > 0 ? 1 : 0;
            sfText_setString(
                ((choices *)inf->current_menu->selected->data)->choice,
                inf->settings->fps[inf->settings->c_fps]);
                sfRenderWindow_setFramerateLimit(inf->win, inf->settings->c_fps
                < 5 ? my_atoi(inf->settings->fps[inf->settings->c_fps]) : 0);
        }
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
    inf->current_menu = inf->others_menu;
    inf->c_menu = OTHERS;
    inf->options_menu->focus = 0;
    inf->others_menu->focus = 1;
}
