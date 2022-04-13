/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_all_menus
*/

#include "rpg.h"

list *init_backgrounds(char **arr, wininf *inf)
{
    list *backgrounds = 0;
    sfVector2f base = {my_atoi(arr[1]), my_atoi(arr[2])};
    sfVector2i size;
    sfVector2f pos;
    for (int i = 0, off = 5; i < my_atoi(arr[3]); i++, off += 5) {
        pos.x = my_atoi(arr[off]) + base.x;
        pos.y = my_atoi(arr[off + 1]) + base.y;
        size.x = my_atoi(arr[off + 2]);
        size.y = my_atoi(arr[off + 3]);
        add_to_list(&backgrounds, generate_textbox(size, inf->atlases.atlas));
        sfSprite_setPosition((sfSprite *)backgrounds->data, pos);
    }
    return backgrounds;
}

choices *fill_choice(char **arr, int tmp, wininf *inf)
{
    sfVector2f pos;
    choices *choice = malloc(sizeof(choices));
    pos = (sfVector2f){my_atoi(arr[tmp + 1]), my_atoi(arr[tmp + 2])};
    choice->choice = init_text(arr[tmp], inf->ui.font, pos);
    pos = (sfVector2f){my_atoi(arr[tmp + 4]), my_atoi(arr[tmp + 5])};
    choice->choice = init_text(arr[tmp + 3], inf->ui.font, pos);
    return choice;
}

list *init_choices(char **arr, wininf *inf, int offset)
{
    list *choices_l = 0;
    sfVector2f base = {my_atoi(arr[1]), my_atoi(arr[2])};
    sfVector2f pos;
    for (int i = 0, tmp = offset + 1; i < my_atoi(arr[offset]); i++, tmp += 7) {
        push_back_double(&choices_l, fill_choice(arr, tmp, inf));
    }
    return choices_l;
}

menuss *init_all_menus(wininf *inf, int menu_id)
{
    menuss *menu = malloc(sizeof(menuss));
    char **arr = my_strtwa(inf->atlases.menus[menu_id], ";\n");
    int offset = my_atoi(arr[3]) * 5 + 4;
    printf("%d\n", offset);
    printf("%s\n", arr[offset]);
    menu->backgrounds = init_backgrounds(arr, inf);
    menu->choices = init_choices(arr, inf, offset);
    return menu;
}
