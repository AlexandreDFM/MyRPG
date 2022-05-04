/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** player_inventory
*/

#include "rpg.h"

invslot *get_item_from_id(int id, wininf *inf)
{
    invslot *slot = malloc(sizeof(invslot));
    slot->id = id;
    if (id == APPLE) {
        slot->line = load_line("<lApple> Apple", FONT_SIZE, inf, malloc);
        slot->use = use_apple;
    }
    if (id == ALMOND) {
        slot->line = load_line("<lChestnut> Apple", FONT_SIZE, inf, malloc);
        slot->use = 0;
    }
    if (id == BANANA) {
        slot->line = load_line("<lBanana> Apple", FONT_SIZE, inf, malloc);
        slot->use = 0;
    }
    return slot;
}

void init_inventory(player *p, int size)
{
    inventory *inv = my_malloc(sizeof(inventory));
    inv->slots = malloc(sizeof(invslot *) * (size + 1));
    for (int i = 0; i <= size; i++) {
        inv->slots[i] = 0;
    }
    p->inv = inv;
}

void add_to_inventory(wininf *inf, inventory *inv, int id)
{
    invslot *slot = get_item_from_id(id, inf);
    for (int i = 0 ; inv->size; i++) {
        if (!inv->slots[i]) {
            inv->slots[i] = slot;
            break;
        }
    }
}

void clean_inventory(inventory *inv)
{
    for (int i = inv->size - 1; i > 0; i++) {
        if (!inv->slots[i]) continue;
        if (!inv->slots[i - 1]) {
            inv->slots[i - 1] = inv->slots[i];
            inv->slots[i] = 0;
            i = inv->size - 1;
        }
    }
}
