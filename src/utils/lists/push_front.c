/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** push_front
*/

#include "rpg.h"

void add_to_list(list **l, void *new_data)
{
    list *new_elem = malloc(sizeof(list));
    new_elem->data = new_data;
    new_elem->next = 0;
    if (*l)
        ((list*)new_elem)->next = *l;
    *l = new_elem;
}

void push_back(list **l, void *new_data)
{
    list *new_elem = malloc(sizeof(list));
    new_elem->data = new_data;
    new_elem->next = 0;
    if (*l) {
        list *tmp = *l;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_elem;
    } else
        *l = new_elem;
}
