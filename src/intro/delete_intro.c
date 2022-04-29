/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** delete_intro
*/

#include "rpg.h"
#include "intro.h"
#include "cinematics_elements.h"

void delete_intro(wininf *inf)
{
    for (int i = 0; i < 3; i++)
        sfSprite_destroy(inf->intro->pkmintro[i].sprite);
    for (int i = 0; i < 4; i++)
        sfSprite_destroy(inf->intro->b_intro[i].sprite);
    sfMusic_stop(inf->intro->i_music1);
    sfMusic_stop(inf->intro->i_music2);
    sfMusic_destroy(inf->intro->i_music1);
    sfMusic_destroy(inf->intro->i_music2);
    free(inf->intro);
    inf->intro = NULL;
}
