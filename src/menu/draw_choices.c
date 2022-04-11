/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** draw_choices
*/

#include "rpg.h"

void draw_choices(wininf *inf, list *choices_l)
{
    sfRenderWindow_drawText(inf->win, ((choices *)choices_l->data)->choice,
    NULL);
    while (choices_l->next != inf->main_menu->head) {
        choices_l = choices_l->next;
        sfRenderWindow_drawText(inf->win,
        ((choices *)choices_l->data)->choice, NULL);
    }
    choices_l = choices_l->next;
}
