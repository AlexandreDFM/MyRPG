/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** move_cursor
*/

#include "rpg.h"
#include "sounds.h"

void move_cursor_up_down(menuss *menu, wininf *inf)
{
    if (inf->inputs.axis.y > 0.0f && !menu->press) {
        sfSound_play(inf->sounds->sounds_board[MENU_MOVE]);
        menu->selected = menu->selected->next; menu->press = 1; menu->blk = 0;
    } if (inf->inputs.axis.y < 0.0f && !menu->press) {
        sfSound_play(inf->sounds->sounds_board[MENU_MOVE]);
        menu->selected = menu->selected->prev; menu->press = 1; menu->blk = 0;
    }
}

void move_cursor(menuss *menu, wininf *inf, player *p)
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
    }
    move_cursor_up_down(menu, inf);
    if (inf->inputs.interact && inf->inputs.can_interact == 0) {
        sfSound_play(inf->sounds->sounds_board[MENU_SELECT]);
        ((choices *)menu->selected->data)->ptrs[0](inf, p);
        inf->inputs.can_interact = 1;
    }
    sfSprite_setPosition(menu->cursor, pos);
}
