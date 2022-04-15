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
    pos = (sfVector2f){my_atoi(arr[tmp + 1]) + my_atoi(arr[1]),
    my_atoi(arr[tmp + 2]) + my_atoi(arr[2])};
    choice->choice = init_text(arr[tmp], inf->ui.font, pos);
    pos = (sfVector2f){my_atoi(arr[tmp + 4]) + my_atoi(arr[1]),
    my_atoi(arr[tmp + 5]) + my_atoi(arr[2])};
    choice->desc = init_text(arr[tmp + 3], inf->ui.font, pos);
    choice->ptr = my_atoi(arr[tmp + 6]);
    return choice;
}

list *init_choices(char **arr, wininf *inf, int off)
{
    if (my_atoi(arr[off]) == 0) return NULL;
    list *choices_l = malloc(sizeof(list));
    choices_l->data = fill_choice(arr, off + 1, inf);
    choices_l->next = NULL;
    choices_l->prev = NULL;
    list *first = choices_l;
    for (int i = 0, tmp = off + 8; i < my_atoi(arr[off]) - 1; i++, tmp += 7) {
        push_back_double(&choices_l, fill_choice(arr, tmp, inf));
    }
    choices_l->next = first;
    choices_l->next->prev = choices_l;
    choices_l = choices_l->next;
    return choices_l;
}

list *fill_texts(char **arr, wininf *inf, int off)
{
    if (my_atoi(arr[off]) == 0) return NULL;
    list *texts = 0;
    sfVector2f pos;
    for (int i = 0, tmp = off + 1; i < my_atoi(arr[off]); i++, tmp += 3) {
        pos.x = my_atoi(arr[tmp + 1]) + my_atoi(arr[1]); pos.y = my_atoi(arr[tmp + 2]) + my_atoi(arr[2]);
        add_to_list(&texts, init_text(arr[tmp], inf->ui.font, pos));
    }
    return texts;
}

menuss *init_all_menus(wininf *inf, int menu_id, int focus)
{
    menuss *menu = malloc(sizeof(menuss));
    char **arr = my_strtwa(inf->atlases.menus[menu_id], ";\n");
    menu->backgrounds = init_backgrounds(arr, inf);
    int offset = my_atoi(arr[3]) * 5 + 4;
    menu->choices = init_choices(arr, inf, offset);
    menu->head = menu->choices;
    menu->selected = menu->choices;
    if (menu->choices) {
        offset += my_atoi(arr[offset]) * 7 + 1;
    } else offset += 1;
    menu->texts = fill_texts(arr, inf, offset);
    if (menu->texts) {
        offset += my_atoi(arr[offset]) * 3 + 2;
        if (!arr[offset + 1]) return menu;
    } else {
        if (!arr[offset + 1]) return menu;
        offset += 2;
    }
    sfVector2f pos = {my_atoi(arr[offset]) + my_atoi(arr[1]),
    my_atoi(arr[offset + 1]) + my_atoi(arr[2])};
    menu->base_pos = pos;
    menu->cursor = set_cursor(inf, (sfVector2f) {my_atoi(arr[offset + 2]),
    my_atoi(arr[offset + 2])}, pos);
    menu->blink = 0;
    menu->pressed = 0;
    menu->focus = focus;
    menu->max_choice = my_atoi(arr[offset + 3]);
    return menu;
}