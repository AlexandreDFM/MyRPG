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
    sfVector2f pos = *(win->dungeon.inf->pos[0]);
    sfVector2i lpos = global_to_local(pos);
    for (int i = 0; i < 100; i++) {
        sfIntRect r = *(win->dungeon.inf->rooms[rand() % win->dungeon.inf->nbr_rooms]);
        int y = rand() % ((r.height - 1) * (r.width - 1));
        // create_enemy(win, &win->dungeon, (sfVector2i){r.left, r.top});
        create_enemy(win, &win->dungeon, (sfVector2i){r.left + (y % (r.width - 1)), r.top + (y / (r.width - 1))});
    }
}
