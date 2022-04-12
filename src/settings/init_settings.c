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
    return setts;
}
