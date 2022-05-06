/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** draw_inv
*/

#include "rpg.h"

void draw_inv(inventory *inv, wininf *inf)
{
    for (int i = 0; i < inv->filled; i++) {
        sfRenderWindow_drawSprite(inf->win, inv->slots[i]->line->sps[0], NULL);
    }
}
