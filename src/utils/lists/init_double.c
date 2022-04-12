/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_double
*/

#include "rpg.h"

choices *create_choice(char **arr, int index, wininf *inf, sfVector2f pos)
{
    choices *choice = malloc(sizeof(choices));
    choice->ptr = my_atoi(arr[index + 2]);
    choice->choice = init_text(arr[index], inf->ui.font, pos);
    choice->desc = init_text(arr[index + 1], inf->ui.font,
    (sfVector2f) {0, 500});
    choice->ptr = my_atoi(arr[index + 2]);
    return choice;
}

list *init_circular(char **arr, wininf *inf, sfVector2f pos, sfVector2f pos2)
{
    pos.x += 50; pos.y -= 15;
    list *n_first;
    list *node = malloc(sizeof(list));
    if (!node) return NULL;
    node->data = create_choice(arr, 6, inf, pos);
    node->next = NULL; node->prev = NULL; n_first = node;
    for (int i = 9; i <= (my_atoi(arr[5]) - 1)* 3 + 6; i += 3) {
        pos.y += inf->menu_padding;
        push_back_double(&node, create_choice(arr, i, inf, pos));
    }
    for (int i = 0; i < my_atoi(arr[5]) - 1; i++) {
        sfText_setPosition(((choices *)node->data)->desc, pos2);
        node = node->next;
    }
    sfText_setPosition(((choices *)node->data)->desc, pos2);
    n_first->prev = node;
    node->next = n_first;
    node = node->next;
    return node;
}
