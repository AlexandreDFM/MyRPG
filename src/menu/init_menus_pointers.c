/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_main_menu_pointers
*/

#include "rpg.h"

void init_main_menu_pointers(wininf *inf)
{
    // inf->main_menu->ptrs[0] = play;
    // inf->main_menu->ptrs[1] = a_log;
    // inf->main_menu->ptrs[2] = options;
    // inf->main_menu->ptrs[3] = my_exit;
}

void init_load_pointers(wininf *inf)
{
    inf->load_menu->ptrs[0] = yes_but;
    inf->load_menu->ptrs[1] = no_but;
}
