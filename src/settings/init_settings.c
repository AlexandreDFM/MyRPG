/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** init_settings
*/

#include "rpg.h"

settings *init_settings(void)
{
    settings *setts = malloc(sizeof(settings));
    setts->show_collision = 0;
    setts->house = 1;
    setts->pokemon = 4;
    setts->c_fps = 0;
    char *fps[6] = {"30", "60", "120", "144", "300", "Max"};
    setts->fps = malloc(sizeof(char *) * 6);
    for (int i = 0; i < 6; i++) setts->fps[i] = my_strdup(fps[i]);
    return setts;
}
