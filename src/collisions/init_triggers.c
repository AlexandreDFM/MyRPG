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
}

void homeext_to_village(wininf *win)
{
    sfVector2f home = (sfVector2f){520.0f, 320.0f};
    sfVector2f village = (sfVector2f){25.0f, 320.0f};
    win->next_scene = win->c_scene == VILLAGE ? HOME : VILLAGE;
    win->next_pos = win->c_scene == VILLAGE ? home : village;
    win->change_scene = 1;
    win->transition = 1;
}

void homeext_to_homeint(wininf *win)
{
    sfVector2f home = (sfVector2f){275.0f, 200.0f};
    sfVector2f interior = (sfVector2f){166.0f, 235.0f};
    win->next_scene = win->c_scene == HOME ? INTERIOR : HOME;
    win->next_pos = win->c_scene == INTERIOR ? home : interior;
    win->transition = 1;
    win->change_scene = 1;
}

void ta_mere(wininf *win)
{
    my_printf("Eh non ta mère :D\n");
    sfVector2f mid = (sfVector2f){520.0f, 320.0f};
    win->next_scene = VILLAGE;
    win->next_pos = mid;
    win->transition = 1;
    win->change_scene = 1;
}

void sleep_and_save(wininf *win)
{
    my_printf("Saving...\n");
    win->change_scene = 0;
    win->transition = 1;
}
