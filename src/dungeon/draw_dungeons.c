/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** draw_dungeons
*/

#include "rpg.h"

void draw_dungeon(wininf *inf, player *p)
{
    sfRenderWindow_drawSprite(inf->win, inf->dungeon.inf->sp, 0);
    for (list *t = inf->dungeon.enemies; t; t = t->next) {
        player *enemy = t->data;
        player_direction_management(inf, enemy);
        sfRenderWindow_drawSprite(inf->win, enemy->test, 0);
    }
}
