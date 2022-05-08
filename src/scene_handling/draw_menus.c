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

void update_equi_pos(wininf *inf, player *p)
{
    sfVector2f pos = sfView_getCenter(inf->camera.view);
    sfVector2f size = sfView_getSize(inf->camera.view);
    sfSprite_setPosition(p->equip_bg_slot,
    (sfVector2f){pos.x + size.x / 2 - 40, pos.y - size.y / 2 + 5});
    sfFloatRect r = sfSprite_getGlobalBounds(p->equip_bg_slot);
    sfSprite_setPosition(p->equip_slot, (sfVector2f){r.left + r.width / 2,
    r.top + r.height / 2});
    r = sfSprite_getGlobalBounds(p->equip_slot);
    sfSprite_setOrigin(p->equip_slot, (sfVector2f){r.width / 2, r.height / 2});
    sfRenderWindow_drawSprite(inf->win, p->equip_bg_slot, 0);
    sfRenderWindow_drawSprite(inf->win, p->equip_slot, 0);
}

void draw_gamemenu(wininf *infos, player *p)
{
    if (infos->c_scene == HOME) draw_home(infos);
    int cs = infos->c_scene;
    if (cs == VILLAGE || cs == BEKIPAN || cs == DOJO || cs == DITTOLAND ||
        cs == INTERIOR)
        draw_static_scene(infos, infos->scenes[infos->c_scene]);
    else if (infos->c_scene == DUNGEON) {
        draw_dungeon(infos, p);
        if (infos->d_items) {
            draw_dropped(infos);
            retrieve_item(infos, p);
        }
    }
    player_direction_management(infos, p);
    draw_player(infos, p); manage_quest(infos);
    if (p->equip_slot) update_equi_pos(infos, p);
    if (infos->transition) {
        update_transition(infos, p);
        sfRenderWindow_drawRectangleShape(infos->win, infos->transi, 0);
    } draw_dialog(infos, p);
    draw_menuui(infos, p);
}
