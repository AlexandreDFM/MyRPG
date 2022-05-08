/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** draw_menus
*/

#include "rpg.h"

void draw_menuui(wininf *infos, player *p)
{
    if (infos->c_menu == PAUSE) {
        draw_menu(infos, infos->pause_menu, p);
        update_playtime(infos);
    }
    if (infos->c_menu != PAUSE && infos->c_menu != NONE) {
        center_menu(infos->current_menu, infos, p);
        draw_menu(infos, infos->current_menu, p);
        if (infos->c_menu == USE_ITEM) {
            center_menu(infos->inventory_menu, infos, p);
            draw_menu(infos, infos->inventory_menu, p);
        }
        if (infos->c_menu == IG_OPTIONS && infos->pressed == 0)
            change_volume_ig(infos);
    }
}

void draw_submenu(wininf *infos, player *p)
{
    if (infos->c_menu == LOAD_SAVE) draw_menu(infos, infos->current_menu, p);
    if (infos->c_menu == OPTIONS){
        draw_menu(infos, infos->current_menu, p);
        if (((choices *)infos->current_menu->selected->data)->ptr < 3
            && infos->pressed == 0) {
            change_volume(infos);
        }
    }
    if (infos->c_menu == KEYBINDS_M)
        draw_menu(infos, infos->change_keys_menu, p);
}

void draw_dropped(wininf *inf)
{
    list *tmp = inf->d_items;
    while (inf->d_items) {
        if (((dropped *)inf->d_items->data)->dropped == 1) {
            sfRenderWindow_drawSprite(inf->win,
            ((dropped *)inf->d_items->data)->data, 0);
        }
        inf->d_items = inf->d_items->next;
    }
    inf->d_items = tmp;
}
