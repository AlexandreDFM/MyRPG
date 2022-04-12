/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** events
*/

#include "infos.h"
#include "inputs.h"

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
        sfKeyUp || inf->event.key.code == sfKeyDown) && inf->c_scene
        == MAIN_MENU)
           inf->current_menu->pressed = 0;
    }
}
