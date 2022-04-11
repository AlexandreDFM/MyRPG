/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** move_cursor
*/

#include "rpg.h"

void up(wininf *inf, sfVector2f *pos)
{
    inf->main_menu->pressed = 1;
    if (inf->main_menu->curr_choice > 0) {
        inf->main_menu->curr_choice -= 1;
        pos->y -= 40;
    } else {
        pos->y = 40 * inf->main_menu->max_choice + inf->main_menu->base_pos.y;
        inf->main_menu->curr_choice = inf->main_menu->max_choice;
    }
    inf->main_menu->selected = inf->main_menu->selected->prev;
}

void down(wininf *inf, sfVector2f *pos)
{
    inf->main_menu->pressed = 1;
    if (inf->main_menu->curr_choice < inf->main_menu->max_choice) {
        inf->main_menu->curr_choice += 1;
        pos->y += 40;
    } else {
        inf->main_menu->curr_choice = 0;
        pos->y = inf->main_menu->base_pos.y;
    }
    inf->main_menu->selected = inf->main_menu->selected->next;
}

void move_cursor(wininf *inf)
{
    sfVector2f pos = sfSprite_getPosition(inf->main_menu->cursor);
    if (sfKeyboard_isKeyPressed(sfKeyDown) && inf->main_menu->pressed == 0) {
        down(inf, &pos);
    }
    if (sfKeyboard_isKeyPressed(sfKeyUp) && !inf->main_menu->pressed) {
        up(inf, &pos);
    }
    if (inf->inputs.interact && inf->inputs.can_interact == 0) {
        inf->inputs.can_interact = 1;
        choices *c = inf->main_menu->selected->data;
        inf->main_menu->ptrs[c->ptr](inf);
    }
    choices *c = (choices*)inf->main_menu->selected->data;
    sfRenderWindow_drawText(inf->win, c->desc, NULL);
    sfSprite_setPosition(inf->main_menu->cursor, pos);
}
