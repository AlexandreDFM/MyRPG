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
    if (inf->intro->plan != PLAN6) {
        if (inf->inputs.attack && inf->inputs.can_attack) {
            inf->inputs.can_attack = 0;
            inf->intro->plan = PLAN5;
        }
    }
    if (inf->intro->plan == PLAN6) {
        if (inf->inputs.attack && inf->inputs.can_attack) {
            inf->inputs.can_attack = 0;
            inf->intro->plan = DELETEINTRO;
        }
    }
}
