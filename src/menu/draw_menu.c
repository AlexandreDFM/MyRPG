/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** draw_menu
*/

#include "rpg.h"

void draw_menu(wininf *inf, menuss *menu)
{
    draw_list(menu->backgrounds, inf->win);
    if (menu->choices)  {
        draw_choices(inf, menu->choices, menu->head);
        sfText *text = ((choices*)menu->selected->data)->desc;
        sfRenderWindow_drawText(inf->win, text, NULL);
    }
    if (menu->texts) draw_list(menu->texts, inf->win);
    if (menu->choices && menu->focus == 1 ) {
        if (menu->blink < 0.4f)
            sfRenderWindow_drawSprite(inf->win, menu->cursor, NULL);
        else if (menu->blink > 0.9f) menu->blink = 0;
        menu->blink += inf->time.dt;
        move_cursor(menu, inf);
    }
}
