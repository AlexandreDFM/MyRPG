/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** my_sfalloc
*/

#include "rpg.h"

void *my_sfalloc(void *(*create)(void), void *(*destroy)(void *))
{
    static list *garbage2 = 0;
    int nbfree = 0;
    if (!create) {
        while (garbage2) {
            list *ne = garbage2->next;
            ((cpp_garbage *)garbage2->data)->destroy(
                ((cpp_garbage *)garbage2->data)->data);
            garbage2 = ne;
            nbfree++;
        }
        my_printf("Freed %d items from CPP automatically\n", nbfree);
        return NULL;
    }
    cpp_garbage *garbage = malloc(sizeof(cpp_garbage));
    if (garbage) {
        list *nl = malloc(sizeof(list));
        garbage->create = create;
        garbage->destroy = destroy;
        garbage->data = garbage->create();
        nl->data = garbage;
        nl->next = garbage2;
        garbage2 = nl;
    } return garbage->data;
}
