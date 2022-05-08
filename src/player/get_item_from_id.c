/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** get_item_from_id
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
