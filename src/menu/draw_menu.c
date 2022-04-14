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
    if (menu->choices) draw_choices(inf, menu->choices, menu->head);
    sfRenderWindow_drawText(inf->win, ((choices *)menu->selected->data)->desc, NULL);
    if (inf->c_menu == NONE) {
        if (menu->blink < 0.4f) sfRenderWindow_drawSprite(inf->win, menu->cursor, NULL);
        else if (menu->blink > 0.9f) menu->blink = 0;
        menu->blink += inf->time.dt;
        move_cursor(menu, inf);
    }
    // if (inf->c_menu == LOAD_SAVE) {
    //     sfRenderWindow_drawSprite(inf->win,inf->load_menu->background, NULL);
    //     sfRenderWindow_drawSprite(inf->win,inf->load_menu->background2, NULL);
    //     sfRenderWindow_drawSprite(inf->win,inf->load_menu->background3, NULL);
    //     draw_choices(inf, inf->load_menu->choices, inf->load_menu->head);
    //     if (inf->load_menu->blink < 0.4f) sfRenderWindow_drawSprite(inf->win, inf->load_menu->cursor, NULL);
    //     else if (inf->load_menu->blink > 0.9f) inf->load_menu->blink = 0;
    //     inf->load_menu->blink += inf->time.dt;
    //     move_cursor(inf->load_menu, inf);
    // }
}
