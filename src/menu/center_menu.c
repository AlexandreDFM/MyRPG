/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** center_menu
*/

#include "rpg.h"

void center_bg(list *bg, char **arr, sfVector2f topl)
{
    sfVector2f pos;
    sfFloatRect pos2 = sfSprite_getGlobalBounds((sfSprite *)bg->data);
    for (int i = 0, off = 4 + (5 * my_atoi(arr[4])); off > 6; i++, off -= 5) {
        pos.x = my_atoi(arr[off - 3]) + topl.x + my_atoi(arr[2]);
        pos.y = my_atoi(arr[off  - 2]) + topl.y + my_atoi(arr[3]);
        sfSprite_setPosition((sfSprite *)bg->data, pos);
        bg = bg->next;
    }
}

void center_choices(menuss *menu, char **arr, sfVector2f topl, int off)
{
    sfVector2f pos;
    list *choice = menu->choices;
    for (int i = 0, tmp = off + 1; i < my_atoi(arr[off]); i++, tmp += 7) {
        pos.x = my_atoi(arr[tmp + 1]) + topl.x + my_atoi(arr[2]);
        pos.y = my_atoi(arr[tmp + 2]) + topl.y + my_atoi(arr[3]) +
        menu->offset * i;
        sfText_setPosition(((choices *)choice->data)->choice, pos);
        pos.x = my_atoi(arr[tmp + 4]) + topl.x + my_atoi(arr[2]);
        pos.y = my_atoi(arr[tmp + 5]) + topl.y + my_atoi(arr[3]);
        sfText_setPosition(((choices *)choice->data)->desc, pos);
        choice = choice->next;
    }
}

void center_texts(menuss *menu, char **arr, sfVector2f topl, int off)
{
    sfVector2f pos;
    list *text = menu->texts;
    for (int i = 0, tmp = off + 1 + my_atoi(arr[off]) * 3; i <
        my_atoi(arr[off]); i++, tmp -= 3) {
        pos.x = my_atoi(arr[tmp - 2]) + topl.x + my_atoi(arr[2]);
        pos.y = my_atoi(arr[tmp - 1]) + topl.y + my_atoi(arr[3]) +
        my_atoi(arr[get_arr_len(arr) - 1]);
        sfText_setPosition(text->data, pos);
        text = text->next;
    }
}

void center_menu(menuss *menu, wininf *inf, player *p)
{
    sfVector2f center = sfView_getCenter(inf->camera.view);
    sfVector2f size = sfView_getSize(inf->camera.view);
    sfVector2f topl = {center.x - size.x / 2, center.y - size.y / 2};
    char **arr = my_strtwa(inf->atlases.menus[menu->id], ";\n");
    sfVector2f new_pos = {topl.x + my_atoi(arr[2]), topl.y + my_atoi(arr[3])};
    sfVector2f tmp_pos;
    center_bg(menu->backgrounds, arr, topl);
    int offset = my_atoi(arr[4]) * 5 + 5;
    if (menu->choices) {
        center_choices(menu, arr, topl, offset);
        offset += my_atoi(arr[offset]) * 7 + 1;
    } else offset += 1;
    center_texts(menu, arr, topl, offset);
}
