/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** main_free
*/

#include "rpg.h"

void end_global_free(components *all)
{
    free_musics(&(all->inf));
}
