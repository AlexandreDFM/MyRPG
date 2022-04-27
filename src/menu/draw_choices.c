/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** draw_choices
*/

#include "rpg.h"

void draw_ig_choices(wininf *inf, list *choices_l, list *head)
{
    sfRenderWindow_drawSprite(inf->win, ((choices *)choices_l->data)->choice,
    NULL);
    while (choices_l->next != head) {
        choices_l = choices_l->next;
        sfRenderWindow_drawSprite(inf->win,
        ((choices *)choices_l->data)->choice, NULL);
    }
    choices_l = choices_l->next;
}

void draw_choices(wininf *inf, list *choices_l, list *head)
{
    sfRenderWindow_drawText(inf->win, ((choices *)choices_l->data)->choice,
    NULL);
    while (choices_l->next != head) {
        choices_l = choices_l->next;
        sfRenderWindow_drawText(inf->win,
        ((choices *)choices_l->data)->choice, NULL);
    }
    choices_l = choices_l->next;
}
