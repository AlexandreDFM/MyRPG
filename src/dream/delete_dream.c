/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** delete_dream
*/

#include "rpg.h"
#include "dream.h"

void delete_dream(wininf *inf)
{
    for (int i = 0; i < 3; i++)
        sfSprite_destroy(inf->dream->b_dream[i].sprite);
    sfMusic_stop(inf->dream->music);
    sfMusic_destroy(inf->dream->music);
    free(inf->dream);
    inf->dream = NULL;
}
