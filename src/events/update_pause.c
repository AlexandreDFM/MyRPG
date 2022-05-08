/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** update_pause
*/

#include "rpg.h"

void update_pause(wininf *inf, player *p)
{
    if (inf->c_scene != INTRO && inf->c_scene != MAIN_MENU &&
    inf->inputs.back && inf->inputs.can_back && inf->c_menu == NONE
    && !inf->ui.dialog) {
        add_to_inventory(inf, inf->inv, rand() % 9);
        inf->c_menu = PAUSE;
        inf->pause_menu->focus = 1;
        inf->current_menu = inf->pause_menu;
        inf->inputs.can_back = 0;
        center_menu(inf->pause_menu, inf, p);
    }
}

void update_pause2(wininf *inf, player *p)
{
    if (inf->c_menu == PAUSE && inf->inputs.back && inf->inputs.can_back &&
    inf->inputs.can_pause) {
        inf->c_menu = NONE;
        inf->inputs.can_back = 0;
        inf->pause_menu->focus = 0;
        inf->pause_menu->selected = inf->pause_menu->head;
        inf->current_menu = inf->main_menu;
    }
    if (inf->c_menu != NONE && inf->c_menu != PAUSE && inf->inputs.pause &&
    inf->inputs.can_pause) {
        inf->inputs.can_pause = 0;
        go_back(inf, p);
    }
}
