/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_main_menu_pointers
*/

#include "rpg.h"

void init_main_menu_pointers(wininf *inf)
{
    void (*ptrs[])(wininf *inf) = {play, a_log, options, my_exit};
    for (int i = 0; i < inf->main_menu->max_choice; i++) {
        ((choices *)inf->main_menu->choices->data)->ptrs[0] = ptrs[i];
        inf->main_menu->choices = inf->main_menu->choices->next;
    }
}

void init_load_pointers(wininf *inf)
{
    ((choices *)inf->load_menu->choices->data)->ptrs[0] = yes_but;
    ((choices *)inf->load_menu->choices->next->data)->ptrs[0] = no_but;
}
