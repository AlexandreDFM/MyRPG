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
        sfKeyUp || inf->event.key.code == sfKeyDown))
            inf->current_menu->pressed = 0;
        if (inf->event.type == sfEvtKeyReleased && inf->event.key.code ==
        sfKeyRControl)
            inf->c_scene = HOME;
        manage_intro(inf);
        if (inf->waiting_key == 1 && inf->event.type == sfEvtKeyPressed) {
            inf->waiting_key = 37; inf->tmp_key = inf->event.key.code;
            printf("%s\n", inf->tmp_key > 0 ? inf->key_list[inf->tmp_key] : "Unknown key");
        }
    }
}
