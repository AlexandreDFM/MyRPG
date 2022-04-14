/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** move_cursor
*/

#include "rpg.h"

void move_cursor(menuss *menu, wininf *inf)
{
    sfVector2f pos = sfSprite_getPosition(menu->cursor);
    if (sfKeyboard_isKeyPressed(sfKeyDown) && !menu->pressed) {
        menu->pressed = 1;
        pos.y = pos.y >= menu->base_pos.y + (menu->max_choice - 1) * 40 ? menu->base_pos.y : pos.y + 40;
        menu->selected = menu->selected->next;
        menu->blink = 0;
    }
    if (sfKeyboard_isKeyPressed(sfKeyUp) && !menu->pressed) {
        menu->pressed = 1;
        pos.y = pos.y <= menu->base_pos.y  ? menu->base_pos.y + (menu->max_choice - 1) * 40 : pos.y - 40;
        menu->selected = menu->selected->prev;
        menu->blink = 0;
    }
    if (inf->inputs.interact && inf->inputs.can_interact == 0) {
        inf->inputs.can_interact = 1;
    }
    sfSprite_setPosition(menu->cursor, pos);
}
