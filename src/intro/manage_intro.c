/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** manage_intro
*/

#include "rpg.h"
#include "intro.h"

void manage_intro(wininf *inf)
{
    if (inf->intro == NULL) return;
    if (inf->intro->valid == 0 && inf->c_scene == INTRO
    && inf->intro->plan != PLAN6) {
        if (inf->event.type == sfEvtKeyPressed
        && inf->event.key.code == sfKeySpace) {
            inf->intro->plan = PLAN5;
        }
    }
    if (inf->intro->valid == 1 && (inf->event.type == sfEvtKeyReleased
    && inf->event.key.code == sfKeySpace)) {
        inf->intro->valid += 1;
    }
    if (inf->intro->valid != 0 && inf->c_scene == INTRO
    && inf->intro->plan == PLAN6) {
        if (inf->intro->valid >= 2 &&
        (inf->event.type == sfEvtKeyPressed
        && inf->event.key.code == sfKeySpace)) {
            inf->intro->plan = DELETEINTRO;
        }
    }
}
