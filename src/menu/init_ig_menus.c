/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_ig_menus
*/

#include "rpg.h"

choices *fill_ig_choice(char **arr, int tmp, wininf *inf, int idx)
{
    int size = my_atoi(arr[1]); sfVector2f pos; sfIntRect r;
    r.left = 0, r.top = 0;
    choices *choice = my_malloc(sizeof(choices));
    pos = (sfVector2f){my_atoi(arr[tmp + 1]) + my_atoi(arr[2]),
    my_atoi(arr[tmp + 2]) + my_atoi(arr[3]) +
    my_atoi(arr[get_arr_len(arr) - 1]) * idx};
    dline *tmp2 = load_line(arr[tmp], size, inf, my_malloc);
    r.width = tmp2->steps[tmp2->max], r.height = tmp2->height;
    choice->choice = tmp2->sps[0];
    sfSprite_setTextureRect(choice->choice, r);
    sfSprite_setPosition(choice->choice, pos);
    pos = (sfVector2f){my_atoi(arr[tmp + 4]) + my_atoi(arr[2]),
    my_atoi(arr[tmp + 5]) + my_atoi(arr[3])};
    tmp2 = load_line(arr[tmp + 3], size, inf, my_malloc);
    r.width = tmp2->steps[tmp2->max], r.height = tmp2->height;
    choice->desc = tmp2->sps[0];
    sfSprite_setPosition(choice->desc, pos);
    sfSprite_setTextureRect(choice->desc, r);
    choice->ptr = my_atoi(arr[tmp + 6]);
    return choice;
}

list *init_ig_choices(char **arr, wininf *inf, int off)
{
    if (my_atoi(arr[off]) == 0) return NULL;
    list *choices_l = my_malloc(sizeof(list));
    choices_l->data = fill_ig_choice(arr, off + 1, inf, 0);
    choices_l->next = NULL;
    choices_l->prev = NULL;
    list *first = choices_l;
    for (int i = 0, tmp = off + 8; i < my_atoi(arr[off]) - 1; i++, tmp += 7) {
        push_back_double(&choices_l, fill_ig_choice(arr, tmp, inf, i + 1));
    }
    choices_l->next = first;
    choices_l->next->prev = choices_l;
    choices_l = choices_l->next;
    return choices_l;
}

list *fill_ig_texts(char **arr, wininf *inf, int off)
{
    int size = my_atoi(arr[1]);
    if (my_atoi(arr[off]) == 0) return NULL;
    list *texts = 0;
    sfVector2f pos;
    dline *tmp2;
    sfIntRect r;
    r.left = 0, r.top = 0;
    for (int i = 0, tmp = off + 1; i < my_atoi(arr[off]); i++, tmp += 3) {
        pos.x = my_atoi(arr[tmp + 1]) + my_atoi(arr[2]);
        pos.y = my_atoi(arr[tmp + 2]) + my_atoi(arr[3]) +
        my_atoi(arr[get_arr_len(arr) - 1]);
        tmp2 = load_line(arr[tmp], size, inf, my_malloc);
        add_to_list(&texts, tmp2->sps[0]);
        r.width = tmp2->steps[tmp2->max], r.height = tmp2->height;
        sfSprite_setTextureRect(texts->data, r);
        sfSprite_setPosition(texts->data, pos);
    }
    return texts;
}

menuss *init_ig2(char **arr, int offset, menuss *menu, wininf *inf)
{
    sfVector2f pos = {my_atoi(arr[offset]) + my_atoi(arr[1]),
    my_atoi(arr[offset + 1]) + my_atoi(arr[2])};
    menu->base_pos = pos;
    menu->cursor = set_cursor(inf, (sfVector2f) {my_atof(arr[offset + 2]),
    my_atof(arr[offset + 3])}, pos);
    menu->blk = 0, menu->press = 0;
    menu->max_choice = my_atoi(arr[offset + 4]);
    menu->type = my_atoi(arr[offset + 6]);
    my_free_array(arr);
    return menu;
}

menuss *init_ig_menus(wininf *inf, int menu_id, int focus)
{
    menuss *menu = my_malloc(sizeof(menuss)); char **arr;
    if (inf->lang == ENGLISH)
        arr = my_strtwa(inf->atlases.menus_en[menu_id], ";\n");
    else arr = my_strtwa(inf->atlases.menus_fr[menu_id], ";\n");
    menu->offset = my_atoi(arr[get_arr_len(arr) - 1]);
    menu->backgrounds = init_backgrounds(arr, inf);
    int offset = my_atoi(arr[4]) * 5 + 5;
    menu->choices = init_ig_choices(arr, inf, offset);
    menu->head = menu->choices; menu->selected = menu->choices;
    if (menu->choices) offset += my_atoi(arr[offset]) * 7 + 1;
    else offset += 1;
    menu->texts = fill_ig_texts(arr, inf, offset);
    if (menu->texts) {
        offset += my_atoi(arr[offset]) * 3 + 2;
        if (!arr[offset + 1]) return menu;
    } else {
        if (!arr[offset + 1]) return menu;
        offset += 2;
    } menu->focus = focus, menu->id = menu_id;
    return init_ig2(arr, offset, menu, inf);
}
