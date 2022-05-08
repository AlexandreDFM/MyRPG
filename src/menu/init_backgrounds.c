/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_backgrounds
*/

#include "rpg.h"

list *init_backgrounds(char **arr, wininf *inf)
{
    list *backgrounds = 0;
    sfVector2f base = {my_atoi(arr[2]), my_atoi(arr[3])};
    sfVector2i size;
    sfVector2f pos;
    for (int i = 0, off = 6; i < my_atoi(arr[4]); i++, off += 5) {
        pos.x = my_atoi(arr[off]) + base.x;
        pos.y = my_atoi(arr[off + 1]) + base.y;
        size.x = my_atoi(arr[off + 2]);
        size.y = my_atoi(arr[off + 3]);
        add_to_list(&backgrounds, generate_textbox(size, inf->atlases.atlas));
        sfSprite_setPosition((sfSprite *)backgrounds->data, pos);
    }
    return backgrounds;
}

int fill_ig_menus(char **arr, menuss *menu, wininf *inf)
{
    menu->offset = my_atoi(arr[get_arr_len(arr) - 1]);
    menu->backgrounds = init_backgrounds(arr, inf);
    int offset = my_atoi(arr[4]) * 5 + 5;
    menu->choices = init_ig_choices(arr, inf, offset);
    menu->head = menu->choices; menu->selected = menu->choices;
    return offset;
}
