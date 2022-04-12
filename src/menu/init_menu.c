/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_menu
*/

#include "rpg.h"

menus *init_menu(wininf *inf, int menu_id)
{
    menus *menu = malloc(sizeof(menus));
    char **arr = my_strtwa(inf->atlases.menus[menu_id], ";\n");
    sfVector2f pos = {my_atoi(arr[1]), my_atoi(arr[2])};
    sfVector2f pos2 = {my_atoi(arr[1]), my_atoi(arr[2])};
    sfVector2i size = {my_atoi(arr[3]), my_atoi(arr[4])};
    menu->background = generate_textbox(size, inf->atlases.atlas);
    size.x = 550, size.y = 100;
    menu->background2 = generate_textbox(size, inf->atlases.atlas);
    menu->cursor = set_cursor(inf, (sfVector2f){3, 3});
    sfSprite_setPosition(menu->background, pos);
    pos2.y += my_atoi(arr[4]) + 50;
    sfSprite_setPosition(menu->background2, pos2);
    menu->base_pos = (sfVector2f) {pos.x + 20, pos.y + 13};
    sfSprite_setPosition(menu->cursor, menu->base_pos);
    menu->choices = malloc(sizeof(list));
    pos2.x += 25; pos2.y += 10;
    menu->choices = init_circular(arr, inf, pos, pos2);
    menu->head = menu->choices;
    menu->selected = menu->choices;
    menu->curr_choice = 0;
    menu->pressed = 0;
    menu->max_choice = my_atoi(arr[5]) - 1;
    menu->blink = 0;
    menu->current = (choices *)menu->head->data;
    return menu;
}
