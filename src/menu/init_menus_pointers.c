/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_main_menu_pointers
*/

#include "rpg.h"

void init_main_menu_pointers(wininf *inf)
{
    void (*ptrs[])(wininf *inf, player *p) = {play, a_log, options, my_exit};
    for (int i = 0; i < inf->main_menu->max_choice; i++) {
        ((choices *)inf->main_menu->choices->data)->ptrs[0] = ptrs[i];
        inf->main_menu->choices = inf->main_menu->choices->next;
    }
}

void init_load_pointers(wininf *inf)
{
    ((choices *)inf->load_menu->choices->data)->ptrs[0] = yes_but;
    ((choices *)inf->load_menu->choices->next->data)->ptrs[0] = go_main;
}

void continue_options_pointers(wininf *inf)
{
    ((choices *)inf->others_menu->choices->data)->ptrs[0] = go_ig_options;
    ((choices *)inf->others_menu->choices->next->data)->ptrs[0] = dummy;
    ((choices *)inf->others_menu->choices->next->next->data)->ptrs[0] =
    my_exit;
    ((choices *)inf->others_menu->choices->prev->data)->ptrs[0] = go_back;
    ((choices *)inf->ig_options_menu->choices->prev->data)->ptrs[0] = go_back;
    ((choices *)inf->use_item_menu->choices->data)->ptrs[0] = use_item;
    ((choices *)inf->use_item_menu->choices->next->data)->ptrs[0] = drop_item;
    ((choices *)inf->use_item_menu->choices->prev->data)->ptrs[0] = equip_item;
}

void init_options_pointers(wininf *inf)
{
    void (*ptrs[])(wininf *inf, player *p) = {change_keybind, options};
    for (int i = 0; i < inf->change_keys_menu->max_choice - 1; i++) {
        ((choices *)inf->change_keys_menu->choices->data)->ptrs[0] = ptrs[0];
        inf->change_keys_menu->choices = inf->change_keys_menu->choices->next;
    }
    ((choices *)inf->change_keys_menu->choices->data)->ptrs[0] = ptrs[1];
    inf->change_keys_menu->choices = inf->change_keys_menu->choices->next;
    ((choices *)inf->options_menu->choices->prev->prev->data)->ptrs[0] =
    go_keybinds;
    ((choices *)inf->options_menu->choices->prev->data)->ptrs[0] = go_main;
    ((choices *)inf->pause_menu->choices->prev->data)->ptrs[0] = go_others;
    ((choices *)inf->pause_menu->choices->data)->ptrs[0] = go_inv;
    ((choices *)inf->pause_menu->choices->next->data)->ptrs[0] = dummy;
    ((choices *)inf->pause_menu->choices->next->next->data)->ptrs[0] = dummy;
    continue_options_pointers(inf);
}
