/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** my_sfalloc
*/

#include "rpg.h"

void *my_sfalloc(int type)
{
    static list *garbage2 = 0;
    int nbfree = 0;
    if (!type) {
        while (garbage2) {
            list *ne = garbage2->next;
            garbage2 = ne;
            nbfree++;
        }
        my_printf("Freed %d items from CPP automatically\n", nbfree);
        return;
}
