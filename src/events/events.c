/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** events
*/

#include "infos.h"
#include "inputs.h"
#include "intro.h"
#include "rpg.h"

void update_pause(wininf *inf, player *p)
{
    if (inf->c_scene != INTRO && inf->c_scene != MAIN_MENU &&
    sfKeyboard_isKeyPressed(inf->inputs.keys.back) && inf->c_menu == NONE &&
    inf->pause_menu->press == 0 && !inf->ui.dialog) {
        inf->c_menu = PAUSE;
        inf->pause_menu->focus = 1;
        inf->pause_menu->press = 1;
        inf->current_menu = inf->pause_menu;
        center_menu(inf->pause_menu, inf, p);
    }
    if (inf->pause_menu->press == 1 &&
        inf->event.type == sfEvtKeyReleased &&
        inf->event.key.code == inf->inputs.keys.back) {
        inf->pause_menu->press = 0;
    }
}

void update_pause2(wininf *inf, player *p)
{
    if (inf->c_menu == PAUSE &&
        sfKeyboard_isKeyPressed(inf->inputs.keys.back)
        && inf->pause_menu->press == 0) {
        inf->c_menu = NONE;
        inf->pause_menu->press = 1;
        inf->pause_menu->focus = 0;
        inf->pause_menu->selected = inf->pause_menu->head;
        inf->current_menu = inf->main_menu;
    }
    if (inf->c_menu != NONE &&
    sfKeyboard_isKeyPressed(inf->inputs.keys.back) && inf->pressed == 0) {
        inf->pressed = 1;
        go_back(inf);
    }
}

void check_back(wininf *inf, player *p)
{
    if (inf->event.type == sfEvtKeyReleased && (inf->event.key.code ==
    inf->inputs.keys.mright || inf->event.key.code ==
    inf->inputs.keys.mleft || inf->event.key.code ==
    inf->inputs.keys.back)) {
        inf->pressed = 0;
    }
}

void update_keys(wininf *inf, player *p)
{
    if (inf->event.type == sfEvtKeyReleased && (inf->event.key.code ==
    inf->inputs.keys.mup || inf->event.key.code == inf->inputs.keys.mdown))
        inf->current_menu->press = 0;
    manage_intro(inf);
    if (inf->waiting_key == 1 && inf->event.type == sfEvtKeyPressed) {
        inf->waiting_key = 37; inf->tmp_key = inf->event.key.code;
    }
    if (inf->waiting_key == 38 && inf->event.type == sfEvtKeyReleased) {
        inf->waiting_key = 0;
        inf->options_menu->focus = 1;
    }
}

void update_events(wininf *inf, player *p)
{
    update_inputs(inf);
    while (sfRenderWindow_pollEvent(inf->win, &inf->event)) {
        if (inf->event.type == sfEvtClosed)
            sfRenderWindow_close(inf->win);
        if (inf->event.type == sfEvtKeyPressed && inf->event.key.code ==
        sfKeyRShift)
            sfRenderWindow_close(inf->win);
        if (inf->event.type == sfEvtKeyPressed && inf->event.key.code ==
        inf->inputs.keys.back && inf->interacting != 0)
            inf->interacting = 0;
        update_keys(inf, p);
        update_pause(inf, p);
        update_pause2(inf, p);
        check_back(inf, p);
    }
}
