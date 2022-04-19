/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** add_collisions
*/

#include "rpg.h"

void draw_circle_col(collision *self, sfRenderWindow *win)
{
    sfRenderWindow_drawCircleShape(win, self->circle, 0);
}

void draw_rect_col(collision *self, sfRenderWindow *win)
{
    sfRenderWindow_drawRectangleShape(win, self->rect, 0);
}
