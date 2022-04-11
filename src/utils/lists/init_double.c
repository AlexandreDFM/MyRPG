/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_double
*/

#include "rpg.h"

choices *create_choice(char **arr, int index, wininf *inf, int ptr)
{
    choices *choice = malloc(sizeof(choices));
    choice->choice = init_text(arr[index], inf->ui.font);
    choice->desc = init_text(arr[index + 1], inf->ui.font);
    choice->ptr = ptr;
    return choice;
}

list *init_circular(char **arr, wininf *inf)
{
    int ptr = 0;
    list *n_first;
    list *node = malloc(sizeof(list));
    if (!node) return NULL;
    node->data = create_choice(arr, 6, inf, ptr);
    node->prev = node;
    node->next = node;
    ptr += 1;
    n_first = node;
    for (int i = 1; i < my_atoi(arr[5]) * 3; i += 3, ptr++) {
        push_back_double(&node, create_choice(arr, i, inf, ptr));
    }
    for (int i = 0; i < my_atoi(arr[5]); i++) node = node->next;
    n_first->prev = node;
    node->prev = n_first;
    node = node->prev;
    return node;
}
