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
