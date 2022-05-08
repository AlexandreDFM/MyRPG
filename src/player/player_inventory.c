/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** player_inventory
*/

#include "rpg.h"

void get_item_from_id2(int id, invslot *slot, wininf *inf)
{
    if (id == PURPLE_BERRY)
        slot->line = load_line("Purple Berry <i_lPurpleBerry>",
        15, inf, malloc);
    if (id == BLUE_BERRY)
        slot->line = load_line("Blue Berry <i_lBlueBerry>", 15, inf, malloc);
    if (id == PINK_BERRY)
        slot->line = load_line("Pink Berry <i_lPinkBerry>", 15, inf, malloc);
    if (id == GREEN_BERRY)
        slot->line = load_line("Green Berry <i_lGreenBerry>", 15, inf, malloc);
    if (id == YELLOW_BERRY)
        slot->line = load_line("Yellow Berry <i_lYellowBerry>",
        15, inf, malloc);
}

invslot *get_item_from_id(int id, wininf *inf)
{
    invslot *slot = my_malloc(sizeof(invslot));
    slot->id = id;
    if (id == APPLE)
        slot->line = load_line("Apple <i_lApple>", 15, inf, malloc);
    if (id == CHESTNUT)
        slot->line = load_line("Chestnut <i_lChestnut>", 15, inf, malloc);
    if (id == BANANA)
        slot->line = load_line("Banana <i_lBanana>", 15, inf, malloc);
    if (id == MEDECINE)
        slot->line = load_line("Medecine <i_lMedecine>", 15, inf, malloc);
    if (id == RED_BERRY)
        slot->line = load_line("Red Berry <i_lRedBerry>", 15, inf, malloc);
    get_item_from_id2(id, slot, inf);
    return slot;
}

void init_inventory(wininf *inf, int size)
{
    inventory *inv = my_malloc(sizeof(inventory));
    inv->slots = my_malloc(sizeof(invslot *) * (size + 1));
    list *tmp = inf->inventory_menu->head;
    for (int i = 0; i <= size; i++, tmp = tmp->next) {
        inv->slots[i] = 0;
        ((choices *)tmp->data)->ptrs[0] = go_use_item;
    }
    inv->filled = 0;
    inv->size = size;
    inf->inv = inv;
}

void change_slot(list *choice, invslot *slot)
{
    sfIntRect r; r.left = 0, r.top = 0;
    r.width = slot->line->steps[slot->line->max];
    r.height = slot->line->height;
    ((choices *)choice->data)->ptrs[0] = go_use_item;
    sfSprite_setTextureRect(slot->line->sps[0], r);
    sfVector2f old_pos = sfSprite_getPosition(((choices *)choice->data)
    ->choice);
    sfSprite_destroy(((choices *)choice->data)->choice);
    ((choices *)choice->data)->choice = slot->line->sps[0];
    sfSprite_setPosition(((choices *)choice->data)->choice, old_pos);

}

void add_to_inventory(wininf *inf, inventory *inv, int id)
{
    invslot *slot = get_item_from_id(id, inf);
    list *tmp = inf->inventory_menu->head;
    for (int i = 0; i < inv->size; i++, tmp = tmp->next) {
        if (!inv->slots[i]) {
            inv->slots[i] = slot;
            inv->filled++;
            inf->ig_slots[i] = slot->line;
            change_slot(tmp, slot);
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
