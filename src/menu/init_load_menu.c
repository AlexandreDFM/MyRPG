/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_load_menu
*/

#include "rpg.h"

void move_buttons(menus *menu)
{
    sfVector2f pos = {1755, 580};
    sfVector2f posc = {1730, 600};
    menu->base_pos = posc;
    sfSprite_setPosition(menu->cursor, posc);
    sfText_setPosition(((choices *)menu->choices->prev->prev->data)->choice, pos);
    pos.x = 1300;
    sfText_setPosition(((choices *)menu->choices->prev->prev->prev->prev->data)->choice, pos);
    pos.x = 1755;
    pos.y += 40;
    sfText_setPosition(((choices *)menu->choices->prev->data)->choice, pos);
    pos.x = 1300;
    sfText_setPosition(((choices *)menu->choices->prev->prev->prev->data)->choice, pos);

}

menus *init_load_menu(wininf *inf, int menu_id)
{
    menus *menu = malloc(sizeof(menus));
    char **arr = my_strtwa(inf->atlases.menus[menu_id], ";\n");
    sfVector2f pos = {my_atoi(arr[1]), my_atoi(arr[2])};
    sfVector2f pos2 = {my_atoi(arr[1]), my_atoi(arr[2]) + my_atoi(arr[4])};
    sfVector2i size = {my_atoi(arr[3]), my_atoi(arr[4])};
    menu->background = generate_textbox(size, inf->atlases.atlas);
    size.x -= 115, size.y = 100;
    menu->background2 = generate_textbox(size, inf->atlases.atlas);
    size.x = 100;
    menu->background3 = generate_textbox(size, inf->atlases.atlas);
    // menu->cursor = set_cursor(inf, (sfVector2f){3, 3});
    sfSprite_setPosition(menu->background, pos);
    pos2.y += 15;
    sfSprite_setPosition(menu->background2, pos2);
    pos2.x += my_atoi(arr[3]) - 100;
    sfSprite_setPosition(menu->background3, pos2);
    menu->base_pos = (sfVector2f) {pos.x + 20, pos.y + 13};
    sfSprite_setPosition(menu->cursor, menu->base_pos);
    menu->choices = malloc(sizeof(list));
    pos.x -= 30; pos.y += 15; inf->menu_padding = 60;
    menu->choices = init_circular(arr, inf, pos, pos2);
    menu->head = menu->choices;
    menu->selected = menu->choices->prev->prev;
    menu->curr_choice = 0;
    menu->pressed = 0;
    menu->max_choice = 1;
    menu->blink = 0;
    move_buttons(menu);
    menu->current = (choices *)menu->head->data;
    return menu;
}
