/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** move_cursor
*/

#include "rpg.h"

void up(menus *menu, sfVector2f *pos)
{
    menu->pressed = 1;
    if (menu->curr_choice > 0) {
        menu->curr_choice -= 1;
        pos->y -= 40;
    } else {
        pos->y = 40 * menu->max_choice + menu->base_pos.y;
        menu->curr_choice = menu->max_choice;
    }
    menu->selected = menu->selected->prev;
    menu->blink = 0;
}

void down(menus *menu, sfVector2f *pos)
{
    menu->pressed = 1;
    if (menu->curr_choice < menu->max_choice) {
        menu->curr_choice += 1;
        pos->y += 40;
    } else {
        menu->curr_choice = 0;
        pos->y = menu->base_pos.y;
    }
    menu->selected = menu->selected->next;
    menu->blink = 0;
}

void move_cursor(menus *menu, wininf *inf)
{
    sfVector2f pos = sfSprite_getPosition(menu->cursor);
    if (sfKeyboard_isKeyPressed(sfKeyDown) && !menu->pressed) {
        down(menu, &pos);
    }
    if (sfKeyboard_isKeyPressed(sfKeyUp) && !menu->pressed) {
        up(menu, &pos);
    }
    if (inf->inputs.interact && inf->inputs.can_interact == 0) {
        inf->inputs.can_interact = 1;
        menu->ptrs[menu->curr_choice](inf);
    }
    sfSprite_setPosition(menu->cursor, pos);
}
