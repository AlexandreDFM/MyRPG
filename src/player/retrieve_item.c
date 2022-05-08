/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** retrieve_item
*/

#include "rpg.h"

void retrieve_item(wininf *inf, player *p)
{
    sfVector2f pos = sfSprite_getPosition(p->test);
    sfFloatRect r;
    list *tmp = inf->d_items;
    while (inf->d_items) {
        r = sfSprite_getGlobalBounds(((dropped *)inf->d_items->data)->data);
        if (sfFloatRect_contains(&r, pos.x, pos.y) &&
        ((dropped *)inf->d_items->data)->dropped) {
            ((dropped *)inf->d_items->data)->dropped = 0;
            add_to_inventory(inf, inf->inv,
            ((dropped *)inf->d_items->data)->id);
        }
        inf->d_items = inf->d_items->next;
    }
    inf->d_items = tmp;
}
