/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** move_cursor
*/

#include "rpg.h"

void move_cursor(menuss *menu, wininf *inf)
{
    sfFloatRect r = menu->type ? sfSprite_getGlobalBounds(
    ((choices *)menu->selected->data)->choice) : sfText_getGlobalBounds(
    ((choices *)menu->selected->data)->choice);
    sfFloatRect rc = sfSprite_getGlobalBounds(menu->cursor); sfVector2f pos;
    if (!menu->type) {
        pos = (sfVector2f){r.left - 25 + (sfSprite_getScale(menu->cursor).x
        < 0 ? r.width + 50 : 0), r.top};
    } else {
        pos = (sfVector2f){r.left - 7 + (sfSprite_getScale(menu->cursor).x < 0
        ? r.width + 15 : 0), r.top + ((r.height - rc.height) / 2)};
    } if (sfKeyboard_isKeyPressed(inf->inputs.keys.mdown) && !menu->press) {
        menu->selected = menu->selected->next; menu->press = 1; menu->blk = 0;
    } if (sfKeyboard_isKeyPressed(inf->inputs.keys.mup) && !menu->press) {
        menu->selected = menu->selected->prev; menu->press = 1; menu->blk = 0;
    } if (inf->inputs.interact && inf->inputs.can_interact == 0) {
        ((choices *)menu->selected->data)->ptrs[0](inf);
        inf->inputs.can_interact = 1;
    }
    sfSprite_setPosition(menu->cursor, pos);
}
