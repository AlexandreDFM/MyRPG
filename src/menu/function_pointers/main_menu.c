/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** main_menu
*/

#include "rpg.h"

void play(wininf *inf)
{
    inf->c_scene = HOME;
    my_printf("Play: %d\n", inf->c_scene);
}

void options(wininf *inf)
{
    my_printf("Options\n");
}

void my_exit(wininf *inf)
{
    my_printf("Exit\n");
}
