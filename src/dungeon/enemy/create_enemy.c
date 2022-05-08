/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_enemy
*/

#include "rpg.h"

void create_enemy(wininf *inf, dungeon *d, sfVector2i pos)
{
    player *new_e = init_player(*inf,  1 + rand() % 49);
    list *nl = malloc(sizeof(list));
    nl->data = new_e;
    nl->next = d->enemies;
    d->enemies = nl;
    sfVector2f np = local_to_global(pos.x, pos.y);
    new_e->target = np;
    new_e->attacking = 0;
    sfSprite_setPosition(new_e->test, np);
}
