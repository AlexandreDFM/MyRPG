/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** equip_item
*/

#include "rpg.h"

void equip_item(wininf *inf, player *p)
{
    if (inf->slot_id == p->equip_slot_id && p->equipped) {
        p->equipped = 0;
        sfSprite_destroy(p->equip_slot);
        p->equip_slot = 0;
        return;
    }
    int id = inf->inv->slots[inf->slot_id]->id;
    p->equip_slot = get_item_sprite(id, inf, p, 0);
    p->equipped = 1;
    p->equip_slot_id = inf->slot_id;
    sfFloatRect r = sfSprite_getGlobalBounds(p->equip_bg_slot);
    sfSprite_setOrigin(p->equip_slot, (sfVector2f){r.width / 2, r.height / 2});
    sfSprite_setPosition(p->equip_slot, (sfVector2f){r.left + r.width / 2,
    r.top + r.height / 2});
}
