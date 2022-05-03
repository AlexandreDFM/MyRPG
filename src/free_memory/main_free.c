/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** main_free
*/

#include "rpg.h"

void my_free_array(char **array)
{
    int i = 0;
    for (; array[i]; i++) {
        free(array[i]);
    }
    free(array);
}

void end_global_free(components *all)
{
    free_musics(&(all->inf));
}
