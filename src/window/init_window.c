/*
** EPITECH PROJECT, 2022
** main
** File description:
** Init of window
*/

#include "infos.h"
#include "inputs.h"

wininf *create_window_infos(void)
{
    wininf *inf = malloc(sizeof(wininf));
    inf->mode = (sfVideoMode){1920, 1080, 32};
    inf->win = sfRenderWindow_create(inf->mode, WINDOW_NAME, sfClose | sfResize, NULL);
    inf->c_scene = HOME;
    init_inputs(inf);
    return inf;
}