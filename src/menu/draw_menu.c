/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** draw_menu
*/

#include "rpg.h"

void draw_menu(wininf *inf)
{
    draw_list(inf->main_menu->backgrounds, inf->win);
    draw_choices(inf, inf->main_menu->choices, inf->main_menu->head);
    sfRenderWindow_drawText(inf->win, ((choices *)inf->main_menu->selected->data)->desc, NULL);
    sfRenderWindow_drawSprite(inf->win, inf->main_menu->cursor, NULL);
    // if (inf->c_menu == NONE) {
        // if (inf->main_menu->blink < 0.4f) sfRenderWindow_drawSprite(inf->win, inf->main_menu->cursor, NULL);
        // // else if (inf->main_menu->blink > 0.9f) inf->main_menu->blink = 0;
        // // inf->main_menu->blink += inf->time.dt;
        // // move_cursor(inf->main_menu, inf);
    // }
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
