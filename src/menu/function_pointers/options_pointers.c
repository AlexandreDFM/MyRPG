/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** options_pointers
*/

#include "rpg.h"

void left_volume(wininf *inf, int current, sfVector2f old_pos, sfIntRect r)
{
    if (inf->event.type == sfEvtKeyPressed && inf->event.key.code ==
    inf->inputs.keys.mleft) {
        if (current == 0 || current == 1) {
            inf->volumes[current] -= inf->volumes[current] > 0 ? 5 : 0;
            inf->ig_choices[current] =
            load_line(my_itoa(inf->volumes[current]), FONT_SIZE, inf, malloc);
            r.width = inf->ig_choices[current]->
            steps[inf->ig_choices[current]->max], r.height =
            inf->ig_choices[current]->height;
            sfSprite_setTextureRect(inf->ig_choices[current]->sps[0], r);
            sfSprite_destroy(((choices *)inf->ig_options_menu->selected->data)
            ->choice);
            ((choices *)inf->ig_options_menu->selected->data)->choice = inf
            ->ig_choices[current]->sps[0];
            sfSprite_setPosition(((choices *)inf->ig_options_menu->selected
            ->data)->choice, old_pos);
        }
    }
}

void right_volume(wininf *inf, int current, sfVector2f old_pos, sfIntRect r)
{
    if (inf->event.type == sfEvtKeyPressed && inf->event.key.code ==
    inf->inputs.keys.mright && (current == 0 || current == 1)) {
        inf->volumes[current] += inf->volumes[current] < 100 ? 5 : 0;
        inf->ig_choices[current] =
        load_line(my_itoa(inf->volumes[current]), FONT_SIZE, inf, malloc);
        r.width = inf->ig_choices[current]->steps[inf->ig_choices[current]
        ->max], r.height = inf->ig_choices[current]->height;
        sfSprite_setTextureRect(inf->ig_choices[current]->sps[0], r);
        sfSprite_destroy(((choices *)inf->ig_options_menu->selected->data)
        ->choice);
        ((choices *)inf->ig_options_menu->selected->data)->choice = inf
        ->ig_choices[current]->sps[0];
        sfSprite_setPosition(((choices *)inf->ig_options_menu->selected
        ->data)->choice, old_pos);
    }
}

void left_fps(wininf *inf, int current, sfVector2f old_pos, sfIntRect r)
{
    if (current == 2 && inf->event.type == sfEvtKeyPressed &&
    inf->event.key.code == inf->inputs.keys.mleft) {
        inf->settings->c_fps -= inf->settings->c_fps > 0 ? 1 : 0;
        inf->ig_choices[current] =
        load_line(inf->settings->fps[inf->settings->c_fps], FONT_SIZE, inf, malloc);
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
    if (current == 2 && inf->event.type == sfEvtKeyPressed &&
    inf->event.key.code == inf->inputs.keys.mright) {
        inf->settings->c_fps += inf->settings->c_fps < 5 ? 1 : 0;
        inf->ig_choices[current] =
        load_line(inf->settings->fps[inf->settings->c_fps], FONT_SIZE, inf, malloc);
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

void change_volume_ig(wininf *inf)
{
    int current = ((choices *)inf->ig_options_menu->selected->data)->ptr;
    sfIntRect r; r.left = 0, r.top = 0;
    sfVector2f old_pos =sfSprite_getPosition(((choices *)inf->ig_options_menu
    ->selected->data)->choice);
    left_volume(inf, current, old_pos, r);
    right_volume(inf, current, old_pos, r);
    left_fps(inf, current, old_pos, r);
    right_fps(inf, current, old_pos, r);
    free(inf->ig_choices[current]->steps);
    free(inf->ig_choices[current]);
}

void change_volume(wininf *inf)
{
    if (inf->event.type == sfEvtKeyPressed && inf->event.key.code ==
    inf->inputs.keys.mright && inf->pressed == 0) {
        inf->pressed = 1;
        if (((choices *)inf->current_menu->selected->data)->ptr == 0) {
            inf->volumes[0] += inf->volumes[0] < 100 ? 5 : 0;
            sfText_setString(
                ((choices *)inf->current_menu->selected->data)->choice,
                my_itoa(inf->volumes[0]));
        }
        if (((choices *)inf->current_menu->selected->data)->ptr == 1) {
            inf->volumes[1] += inf->volumes[1] < 100 ? 5 : 0;
            sfText_setString(
                ((choices *)inf->current_menu->selected->data)->choice,
                my_itoa(inf->volumes[1]));
        }
        if (((choices *)inf->current_menu->selected->data)->ptr == 2) {
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
            inf->volumes[0] -= inf->volumes[0] > 0 ? 5 : 0;
            sfText_setString(
                ((choices *)inf->current_menu->selected->data)->choice,
                my_itoa(inf->volumes[0]));
        } if (((choices *)inf->current_menu->selected->data)->ptr == 1) {
            inf->volumes[1] -= inf->volumes[1] > 0 ? 5 : 0;
            sfText_setString(
                ((choices *)inf->current_menu->selected->data)->choice,
                my_itoa(inf->volumes[1]));
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
