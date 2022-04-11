/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** draw_menu
*/

#include "rpg.h"

void draw_menu(wininf *inf)
{
    sfRenderWindow_drawSprite(inf->win,inf->main_menu->background, NULL);
    sfRenderWindow_drawSprite(inf->win,inf->main_menu->background2, NULL);
    draw_choices(inf, inf->main_menu->choices);
    sfRenderWindow_drawSprite(inf->win, inf->main_menu->cursor, NULL);
    move_cursor(inf);
}
