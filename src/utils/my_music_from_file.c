/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** my_music_from_file
*/

#include "rpg.h"

sfMusic *my_music_from_file(char *path)
{
    static list *garbage2 = 0;
    int nbfree = 0;
    if (!path) {
        while (garbage2) {
            list *ne = garbage2->next;
            sfMusic_destroy(garbage2->data);
            free(garbage2);
            garbage2 = ne;
            nbfree++;
        }
        my_printf(stdout, "Freed %d music%s automatically\n", nbfree,
        (nbfree > 1 ? "s" : ""));
        return NULL;
    }
    void *data = sfMusic_createFromFile(path);
    if (data) {
        list *nl = malloc(sizeof(list));
        nl->data = data; nl->next = garbage2;
        garbage2 = nl;
    } return data;
}
