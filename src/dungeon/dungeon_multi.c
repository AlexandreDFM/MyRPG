/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** generation
*/

#include "rpg.h"

void treat_dungeon_sync(wininf *win, int id)
{
    if (win->net->is_multi) {
        sfSprite *sp = win->dungeon.inf->sp;
        win->dungeon.inf->sp = 0;
        add_ord(DUNGEONSYNC, win->dungeon.inf, sizeof(win->dungeon.inf),
            win->net->packet);
        add_ord(APPEND, &id, sizeof(int), win->net->packet);
        win->dungeon.inf->sp = sp;
    }
}
