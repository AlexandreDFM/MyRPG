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

void draw_special_scene(wininf *infos, player *p)
{
    if (infos->c_scene == INTRO) draw_intro(infos);
    if (infos->c_scene == DREAM) draw_dream(infos);
    if (infos->c_scene == QUIZ) draw_quiz(infos, p);
    if (infos->c_scene == DITTO) draw_ditto(infos);
}

void draw_gamemenu(wininf *infos, player *p)
{
    if (infos->c_scene == HOME)
        draw_home(infos);
    int cs = infos->c_scene;
    if (cs == VILLAGE || cs == BEKIPAN || cs == DOJO || cs == DITTOLAND ||
        cs == INTERIOR)
        draw_static_scene(infos, infos->scenes[infos->c_scene]);
    else if (infos->c_scene == DUNGEON)
        draw_dungeon(infos, p);
    player_direction_management(infos, p);
    draw_player(infos, p);
    if (infos->transition) {
        update_transition(infos, *p);
        sfRenderWindow_drawRectangleShape(infos->win, infos->transi, 0);
    }
    draw_dialog(infos, p);
    draw_menuui(infos, p);
}
