/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** scene_triggers
*/

#include "rpg.h"

void homeext_to_village(wininf *win, player *p)
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

void homeext_to_homeint(wininf *win, player *p)
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

void village_to_bekipan(wininf *win, player *p)
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

void village_to_dojo(wininf *win, player *p)
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

void village_to_dittoland(wininf *win, player *p)
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
