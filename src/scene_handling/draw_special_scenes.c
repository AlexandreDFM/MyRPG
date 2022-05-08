/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** draw_menus
*/

#include "rpg.h"

void draw_special_scene(wininf *infos, player *p)
{
    if (infos->c_scene == INTRO) draw_intro(infos);
    if (infos->c_scene == DREAM) draw_dream(infos);
    if (infos->c_scene == QUIZ) draw_quiz(infos, p);
    if (infos->c_scene == DITTO) draw_ditto(infos);
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

void continue_gamemenu(wininf *infos, player *p)
{
    if (infos->transition) {
        update_transition(infos, p);
        sfRenderWindow_drawRectangleShape(infos->win, infos->transi, 0);
    }
    update_transition(infos, p);
    sfRenderWindow_drawRectangleShape(infos->win, infos->transi, 0);
    draw_dialog(infos, p); draw_menuui(infos, p);
}

void draw_gamemenu(wininf *infos, player *p)
{
    if (infos->c_scene == HOME) draw_home(infos);
    int cs = infos->c_scene;
    if (cs == VILLAGE || cs == BEKIPAN || cs == DOJO || cs == DITTOLAND ||
        cs == INTERIOR || cs == BOSS) {
        draw_static_scene(infos, infos->scenes[cs]);
    } else if (infos->c_scene == DUNGEON) {
        draw_dungeon(infos, p);
        if (infos->d_items) {
            draw_dropped(infos);
            retrieve_item(infos, p);
        }
    }
    player_direction_management(infos, p);
    draw_player(infos, p);
    manage_quest(infos);
    draw_hud(infos, p);
    if (p->equip_slot) update_equi_pos(infos, p);
    continue_gamemenu(infos, p);
}

void draw_hud(wininf *inf, player *p)
{
    sfVector2f pos = sfView_getCenter(inf->camera.view);
    sfVector2f size = sfView_getSize(inf->camera.view);
    int off[4] = {0, 30, 60, 90};
    for (int i = 0; i < 4; i++) {
        sfSprite_setPosition(inf->ui.hud[i], (sfVector2f){
        pos.x - size.x / 2 + 5 + off[i], pos.y - size.y / 2 + 2});
        sfRenderWindow_drawSprite(inf->win, inf->ui.hud[i], 0);
    }
    sfText_setString(inf->ui.hp[0], my_itoa(p->st.health));
    sfText_setString(inf->ui.hp[1], my_itoa(p->st.max_health));
    for (int i = 0; i < 2; i++) {
        sfText_setPosition(inf->ui.hp[i], (sfVector2f){
        pos.x - size.x / 2 + 5 + off[i + 1] + 15 - (7 * i), pos.y -
        size.y / 2 - 3});
        sfRenderWindow_drawText(inf->win, inf->ui.hp[i], 0);
    }
}
