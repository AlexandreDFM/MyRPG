/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** move_cursor
*/

#include "rpg.h"

void move_cursor(menuss *menu, wininf *inf)
{
    sfFloatRect r = sfText_getGlobalBounds(
    ((choices *)menu->selected->data)->choice);
    sfVector2f pos = {r.left - 25 + (sfSprite_getScale(menu->cursor).x < 0 ?
    + r.width + 50 : 0), r.top};
    if (sfKeyboard_isKeyPressed(inf->inputs.keys.mdown) && !menu->pressed) {
        menu->selected = menu->selected->next;
        menu->pressed = 1; menu->blink = 0;
    }
    if (sfKeyboard_isKeyPressed(inf->inputs.keys.mup) && !menu->pressed) {
        menu->selected = menu->selected->prev;
        menu->pressed = 1; menu->blink = 0;
    }
    if (inf->inputs.interact && inf->inputs.can_interact == 0) {
        ((choices *)menu->selected->data)->ptrs[0](inf);
        inf->inputs.can_interact = 1;
    }
    sfSprite_setPosition(menu->cursor, pos);
}
