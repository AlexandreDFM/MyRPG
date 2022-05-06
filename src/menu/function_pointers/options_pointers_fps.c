/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** options_pointers
*/

#include "rpg.h"

void left_fps(wininf *inf, int current, sfVector2f old_pos, sfIntRect r)
{
    if (current == 2 && inf->inputs.axis.x < 0) {
        inf->pressed = 1;
        inf->settings->c_fps -= inf->settings->c_fps > 0 ? 1 : 0;
        inf->ig_choices[current] =
        load_line(inf->settings->fps[inf->settings->c_fps], FONT_SIZE, inf,
        malloc);
        r.width = inf->ig_choices[current]->steps[inf->ig_choices[current]
        ->max], r.height = inf->ig_choices[current]->height;
        sfSprite_setTextureRect(inf->ig_choices[current]->sps[0], r);
        sfSprite_destroy(((choices *)inf->ig_options_menu->selected->data)
        ->choice);
        ((choices *)inf->ig_options_menu->selected->data)->choice = inf
        ->ig_choices[current]->sps[0];
        sfSprite_setPosition(((choices *)inf->ig_options_menu->selected
        ->data)->choice, old_pos);
        sfRenderWindow_setFramerateLimit(inf->win, inf->settings->c_fps < 5 ?
        my_atoi(inf->settings->fps[inf->settings->c_fps]) : 0);
    }
}

void right_fps(wininf *inf, int current, sfVector2f old_pos, sfIntRect r)
{
    if (current == 2 && inf->inputs.axis.x > 0) {
        inf->pressed = 1;
        inf->settings->c_fps += inf->settings->c_fps < 5 ? 1 : 0;
        inf->ig_choices[current] =
        load_line(inf->settings->fps[inf->settings->c_fps], FONT_SIZE, inf,
        malloc);
        r.width = inf->ig_choices[current]->steps[inf->ig_choices[current]
        ->max], r.height = inf->ig_choices[current]->height;
        sfSprite_setTextureRect(inf->ig_choices[current]->sps[0], r);
        sfSprite_destroy(((choices *)inf->ig_options_menu->selected->data)
        ->choice);
        ((choices *)inf->ig_options_menu->selected->data)->choice = inf
        ->ig_choices[current]->sps[0];
        sfSprite_setPosition(((choices *)inf->ig_options_menu->selected
        ->data)->choice, old_pos);
        sfRenderWindow_setFramerateLimit(inf->win, inf->settings->c_fps < 5 ?
        my_atoi(inf->settings->fps[inf->settings->c_fps]) : 0);
    }
}

void right_main_fps(wininf *inf)
{
    if (((choices *)inf->current_menu->selected->data)->ptr == 2) {
        inf->settings->c_fps += inf->settings->c_fps < 5 ? 1 : 0;
        sfText_setString(
            ((choices *)inf->current_menu->selected->data)->choice,
            inf->settings->fps[inf->settings->c_fps]);
        sfRenderWindow_setFramerateLimit(inf->win, inf->settings->c_fps < 5 ?
        my_atoi(inf->settings->fps[inf->settings->c_fps]) : 0);
    }
}

void left_main_fps(wininf *inf)
{
    if (((choices *)inf->current_menu->selected->data)->ptr == 2) {
        inf->settings->c_fps -= inf->settings->c_fps > 0 ? 1 : 0;
        sfText_setString(
            ((choices *)inf->current_menu->selected->data)->choice,
            inf->settings->fps[inf->settings->c_fps]);
        sfRenderWindow_setFramerateLimit(inf->win, inf->settings->c_fps < 5 ?
        my_atoi(inf->settings->fps[inf->settings->c_fps]) : 0);
    }
}
