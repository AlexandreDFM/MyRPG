/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** main_menu
*/

#include "rpg.h"

void go_keybinds(wininf *inf, player *p)
{
    inf->prev_menu = inf->current_menu;
    inf->current_menu = inf->change_keys_menu;
    inf->c_menu = KEYBINDS_M;
    inf->main_menu->focus = 0;
    inf->options_menu->focus = 0;
    inf->change_keys_menu->focus = 1;
    inf->prev_menu = inf->options_menu;
}

void my_exit(wininf *inf, player *p)
{
    sfRenderWindow_close(inf->win);
}

void a_log(wininf *inf, player *p)
{
    inf->c_scene = HOME;
}

void go_back(wininf *inf, player *p)
{
    if (inf->c_menu == OPTIONS || inf->c_menu == LOAD_SAVE)
        go_main(inf, p);
    if (inf->c_menu == KEYBINDS_M)
        options(inf, p);
    if (inf->c_menu == OTHERS || inf->c_menu == INVENTORY)
        go_pause(inf, p);
    if (inf->c_menu == IG_OPTIONS)
        go_others(inf, p);
    if (inf->c_menu == USE_ITEM)
        go_inv(inf, p);
}
