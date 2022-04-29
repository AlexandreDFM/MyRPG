/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** delete_ditto
*/

#include "rpg.h"
#include "ditto.h"

void delete_ditto(wininf *inf)
{
    for (int i = 0; i < 3; i++)
        sfSprite_destroy(inf->ditto->ditto[i].sprite);
    sfMusic_stop(inf->ditto->conga);
    sfMusic_destroy(inf->ditto->conga);
    free(inf->ditto);
    inf->ditto = NULL;
}
