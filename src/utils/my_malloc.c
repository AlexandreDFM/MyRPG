/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** my_malloc
*/

#include "rpg.h"

void *my_malloc(size_t size)
{
    static list *garbage = 0;
    int nbfree = 0;
    if (!size) {
        while (garbage) {
            list *ne = garbage->next;
            free(garbage->data);
            free(garbage);
            garbage = ne;
            nbfree++;
        } my_printf(stderr, "Freed %d items automatically\n", nbfree);
        return 0;
    }
    void *data = malloc(size);
    if (data) {
        list *nl = malloc(sizeof(list));
        nl->data = data;
        nl->next = garbage;
        garbage = nl;
    } return data;
}
