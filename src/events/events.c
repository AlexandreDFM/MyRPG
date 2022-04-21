/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** events
*/

#include "infos.h"
#include "inputs.h"
#include "intro.h"

void update_events(wininf *inf)
{
    update_inputs(inf);
    while (sfRenderWindow_pollEvent(inf->win, &inf->event)) {
        if (inf->event.type == sfEvtClosed)
            sfRenderWindow_close(inf->win);
        if (inf->event.type == sfEvtKeyPressed && inf->event.key.code ==
        sfKeyRShift)
            sfRenderWindow_close(inf->win);
        if (inf->event.type == sfEvtKeyPressed && inf->event.key.code ==
        sfKeyEscape)
            inf->interacting = 0;
        if (inf->event.type == sfEvtKeyReleased && (inf->event.key.code ==
        inf->inputs.keys.mup || inf->event.key.code == inf->inputs.keys.mdown))
            inf->current_menu->pressed = 0;
        if (inf->event.type == sfEvtKeyReleased && inf->event.key.code ==
        sfKeyRControl)
            inf->c_scene = HOME;
        manage_intro(inf);
        if (inf->waiting_key == 1 && inf->event.type == sfEvtKeyPressed) {
            inf->waiting_key = 37; inf->tmp_key = inf->event.key.code;
        }
        if (inf->waiting_key == 38 && inf->event.type == sfEvtKeyReleased) {
            inf->waiting_key = 0;
            inf->options_menu->focus = 1;
        }
        if ((inf->c_menu == OPTIONS || inf->c_menu == LOAD_SAVE) && sfKeyboard_isKeyPressed(inf->inputs.keys.back))
            go_back(inf);
    }
}
