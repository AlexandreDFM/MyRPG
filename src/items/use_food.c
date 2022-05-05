/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** use_food
*/

#include "rpg.h"

void use_apple(wininf *inf, invslot **slot)
{
    my_printf(1, "Eaten an apple\n");
    sfTexture_destroy((*slot)->line->img);
    free((*slot)->line->steps);
    sfSprite_destroy((*slot)->line->sps[0]);
    free((*slot)->line->sps);
    free(*slot);
    *slot = 0;
}

void drop_item(int id)
{
    my_printf(1, "Dropped a %d\n");
}
