/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** generation
*/

#include "rpg.h"

void create_dungeon(wininf *win, char *name)
{
    sfImage *img = sfImage_createFromFile(name);
    win->dungeon.inf = generate_map(3, img);
    win->dungeon.in = 1;
    for (int i = 0; win->dungeon.inf->map[i]; i++) {
        printf("%s\n", win->dungeon.inf->map[i]);
    }
    sfVector2f pos = *(win->dungeon.inf->pos[0]); //TEMP
    sfVector2i lpos = global_to_local(pos);
    create_enemy(win, &win->dungeon, (sfVector2i){lpos.x - 2, lpos.y});
}
