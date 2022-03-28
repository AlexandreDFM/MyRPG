/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** scene_handler
*/

#include "infos.h"
#include "scenes.h"

void handle_scene(wininf *infos)
{
    sfRenderWindow_clear(infos->win, sfBlack);
    
    sfRenderWindow_display(infos->win);
}