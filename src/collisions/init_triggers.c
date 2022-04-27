/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_triggers
*/

#include "rpg.h"

void create_triggers(wininf *inf)
{
    inf->triggers[0] = homeext_to_village;
    inf->triggers[1] = homeext_to_homeint;
    inf->triggers[2] = ta_mere;
    inf->triggers[3] = sleep_and_save;
    inf->triggers[4] = interact_pnj;
    inf->triggers[5] = village_to_bekipan;
    inf->triggers[6] = village_to_dittoland;
    inf->triggers[7] = village_to_dojo;
    inf->triggers[8] = generate_random_dungeon;
}

void homeext_to_village(wininf *win, player p)
{
    sfVector2f home = (sfVector2f){520.0f, 320.0f};
    sfVector2f village = (sfVector2f){25.0f, 320.0f};
    win->next_scene = win->c_scene == VILLAGE ? HOME : VILLAGE;
    win->next_pos = win->c_scene == VILLAGE ? home : village;
    win->transition = 1;
    win->change_scene = 1;
    if (win->net->is_multi) {
        add_ord(SETPOS, &win->next_pos, sizeof(sfVector2f), win->net->packet);
        add_ord(CHANGE_SCENE, &win->next_scene, sizeof(int), win->net->packet);
    }
}

void homeext_to_homeint(wininf *win, player p)
{
    sfVector2f home = (sfVector2f){275.0f, 200.0f};
    sfVector2f interior = (sfVector2f){166.0f, 235.0f};
    win->next_scene = win->c_scene == HOME ? INTERIOR : HOME;
    win->next_pos = win->c_scene == INTERIOR ? home : interior;
    win->transition = 1;
    win->change_scene = 1;
    if (win->net->is_multi) {
        add_ord(SETPOS, &win->next_pos, sizeof(sfVector2f), win->net->packet);
        add_ord(CHANGE_SCENE, &win->next_scene, sizeof(int), win->net->packet);
    }
}

void ta_mere(wininf *win, player p)
{
    my_printf("Eh non ta mère :D\n");
    sfVector2f mid = (sfVector2f){520.0f, 320.0f};
    win->next_scene = VILLAGE;
    win->next_pos = mid;
    win->transition = 1;
    win->change_scene = 1;
    if (win->net->is_multi) {
        add_ord(SETPOS, &win->next_pos, sizeof(sfVector2f), win->net->packet);
        add_ord(CHANGE_SCENE, &win->next_scene, sizeof(int), win->net->packet);
    }
}

void village_to_bekipan(wininf *win, player p)
{
    sfVector2f home = (sfVector2f){940.0f, 325.0f};
    sfVector2f interior = (sfVector2f){12.5f, 216.5f};
    win->next_scene = win->c_scene == VILLAGE ? BEKIPAN : VILLAGE;
    win->next_pos = win->c_scene == BEKIPAN ? home : interior;
    win->transition = 1;
    win->change_scene = 1;
    if (win->net->is_multi) {
        add_ord(SETPOS, &win->next_pos, sizeof(sfVector2f), win->net->packet);
        add_ord(CHANGE_SCENE, &win->next_scene, sizeof(int), win->net->packet);
    }
}

void village_to_dojo(wininf *win, player p)
{
    sfVector2f home = (sfVector2f){531.5f, 687.0f};
    sfVector2f interior = (sfVector2f){340.0f, 22.0f};
    win->next_scene = win->c_scene == VILLAGE ? DOJO : VILLAGE;
    win->next_pos = win->c_scene == DOJO ? home : interior;
    win->transition = 1;
    win->change_scene = 1;
    if (win->net->is_multi) {
        add_ord(SETPOS, &win->next_pos, sizeof(sfVector2f), win->net->packet);
        add_ord(CHANGE_SCENE, &win->next_scene, sizeof(int), win->net->packet);
    }
}

void village_to_dittoland(wininf *win, player p)
{
    sfVector2f home = (sfVector2f){232.0f, 509.0f};
    sfVector2f interior = (sfVector2f){520.0f, 40.0f};
    win->next_scene = win->c_scene == VILLAGE ? DITTOLAND : VILLAGE;
    win->next_pos = win->c_scene == DITTOLAND ? interior : home;
    win->transition = 1;
    win->change_scene = 1;
    if (win->net->is_multi) {
        add_ord(SETPOS, &win->next_pos, sizeof(sfVector2f), win->net->packet);
        add_ord(CHANGE_SCENE, &win->next_scene, sizeof(int), win->net->packet);
    }
}

void generate_random_dungeon(wininf *win, player p)
{
    sfVector2f home = (sfVector2f){0.0f, 0.0f};
    sfVector2f interior = (sfVector2f){0.0f, 0.0f};
    win->next_scene = win->c_scene == HOME ? DUNGEON : HOME;
    win->next_pos = win->c_scene == DUNGEON ? interior : home;
    win->transition = 1;
    win->change_scene = 1;
    if (win->net->is_multi) {
        add_ord(SETPOS, &win->next_pos, sizeof(sfVector2f), win->net->packet);
        add_ord(CHANGE_SCENE, &win->next_scene, sizeof(int), win->net->packet);
    }
}

void interact_pnj(wininf *win, player p)
{
    float min = 200.f;
    pnj *closest = 0;
    list *l = win->scenes[win->c_scene].pnjs;
    for (list *t = l; t; t = t->next) {
        pnj *cp = t->data;
        float cmin = manhattan_distance(sfSprite_getPosition(p.test), cp->pos);
        if (cmin < min) {
            min = cmin;
            closest = cp;
        }
    }
    sfVector2f poubelle = sfView_getCenter(win->camera.view);
    poubelle.y += 45.0f;
    sfSprite_setPosition(win->ui.background, poubelle);
    win->interacting = 1;
    if (!win->ui.dialog)
        win->ui.dialog = create_dialog_list(win, closest->dialog, poubelle);
    else {
        dline *c_line = (dline*)win->ui.dialog->data;
        if (c_line->i == c_line->max) {
            win->ui.dialog = win->ui.dialog->next;
            win->interacting = !win->ui.dialog ? 0 : win->interacting;
        } else {
            c_line->i = c_line->max - 1;
        }
    }
}

void sleep_and_save(wininf *win, player p)
{
    my_printf("Saving...\n");
    win->change_scene = 0;
    win->transition = 1;
}
