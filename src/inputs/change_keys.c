/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** change_keys
*/

#include "rpg.h"

sfKeyCode check_key_valid(wininf *inf)
{
    if (inf->inputs.keys.up == inf->tmp_key) return -1;
    if (inf->inputs.keys.down == inf->tmp_key) return -1;
    if (inf->inputs.keys.left == inf->tmp_key) return -1;
    if (inf->inputs.keys.right == inf->tmp_key) return -1;
    if (inf->inputs.keys.interact == inf->tmp_key) return -1;
    if (inf->inputs.keys.inventory == inf->tmp_key) return -1;
    if (inf->inputs.keys.attack == inf->tmp_key) return -1;
    if (inf->inputs.keys.back == inf->tmp_key) return -1;
    return inf->tmp_key;
}

void update_temporary_key(wininf *inf)
{
    if (inf->key_change == 0) inf->inputs.keys.up = inf->tmp_key;
    if (inf->key_change == 1) inf->inputs.keys.down = inf->tmp_key;
    if (inf->key_change == 2) inf->inputs.keys.left = inf->tmp_key;
    if (inf->key_change == 3) inf->inputs.keys.right = inf->tmp_key;
    if (inf->key_change == 4) inf->inputs.keys.interact = inf->tmp_key;
    if (inf->key_change == 5) inf->inputs.keys.inventory = inf->tmp_key;
    if (inf->key_change == 6) inf->inputs.keys.attack = inf->tmp_key;
    if (inf->key_change == 7) inf->inputs.keys.back = inf->tmp_key;
    if (inf->key_change == 8) inf->inputs.keys.mup = inf->tmp_key;
    if (inf->key_change == 9) inf->inputs.keys.mdown = inf->tmp_key;
    if (inf->key_change == 10) inf->inputs.keys.mleft = inf->tmp_key;
    if (inf->key_change == 11) inf->inputs.keys.mright = inf->tmp_key;
}

void update_key(wininf *inf)
{
    if (check_key_valid(inf) >= 0)
        update_temporary_key(inf);
    inf->waiting_key = 38;
    inf->key_change = -1;
    sfText *tmp_t = ((choices *)inf->current_menu->selected->data)->choice;
    sfVector2f pos = sfText_getPosition(tmp_t);
    pos.y -= 20;
    sfText_setPosition(tmp_t, pos);
    sfText_setString(tmp_t, inf->tmp_key >= 0 ?
    inf->key_list[inf->tmp_key] : "Unknown key");

}
