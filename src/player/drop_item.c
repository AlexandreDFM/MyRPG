/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** drop_item
*/

#include "rpg.h"

dline *update_ig_choice(char *str, sfSprite *data, wininf *inf)
{
    dline *line = load_line(str, FONT_SIZE, inf, malloc);
    sfIntRect r; r.left = 0, r.top = 0;
    r.width = line->steps[line->max]; r.height = line->height;
    sfSprite_setTextureRect(line->sps[0], r);
    sfVector2f old_pos = sfSprite_getPosition(data);
    sfSprite_setPosition(line->sps[0], old_pos);
    return line;
}

void drop_item(wininf *inf)
{
    free(inf->ig_slots[inf->slot_id]->steps);
    inf->ig_slots[inf->slot_id] = update_ig_choice("Empty",
    ((choices *)inf->current_menu->selected->data)->choice, inf);
    list *tmp = inf->inventory_menu->head;
    int i = 0;
    for (; i < inf->slot_id; i++, tmp = tmp->next);
    printf("%d\n", inf->inv->slots[i]->id);
    sfSprite_destroy(((choices*)tmp->data)->choice);
    sfTexture_destroy(inf->inv->slots[inf->slot_id]->line->img);
    inf->inv->slots[inf->slot_id] = 0;
    ((choices *)tmp->data)->choice = inf->ig_slots[inf->slot_id]->sps[0];
    go_inv(inf);
}

// void use_item(wininf *inf)
// {
//     inf->atlases.items[]
// }
