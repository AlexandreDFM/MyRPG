/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** generation
*/

#include "rpg.h"

sfImage *get_dungeon_image(sfImage *atlas, int id)
{
    sfIntRect r = (sfIntRect){5992 + 144 * id, 0, 144, 1128};
    sfTexture *tex = sfTexture_createFromImage(atlas, &r);
    sfImage *cdungeon = sfTexture_copyToImage(tex);
    sfTexture_destroy(tex);
    return cdungeon;
}

void create_dungeon(wininf *win, int id)
{
    sfImage *img = get_dungeon_image(win->atlases.atlas, id);
    win->dungeon.inf = generate_map(3, img);
    sfImage_destroy(img);
    if (win->net->is_multi) {
        sfSprite *sp = win->dungeon.inf->sp;
        win->dungeon.inf->sp = 0;
        add_ord(DUNGEONSYNC, win->dungeon.inf, sizeof(win->dungeon.inf),
            win->net->packet);
        add_ord(APPEND, &id, sizeof(int), win->net->packet);
        win->dungeon.inf->sp = sp;
    }
    win->dungeon.in = 1;
    sfVector2f pos = *(win->dungeon.inf->pos[0]);
    sfVector2i lpos = global_to_local(pos);
    create_enemy(win, &win->dungeon, (sfVector2i){lpos.x + 2, lpos.y + 2});
    // for (int i = 0; i < 100; i++) {
    //     sfIntRect r = *(win->dungeon.inf->rooms[rand() % win->dungeon.inf->nbr_rooms]);
    //     int y = rand() % ((r.height - 1) * (r.width - 1));
    //     create_enemy(win, &win->dungeon, (sfVector2i){r.left + (y % (r.width - 1)), r.top + (y / (r.width - 1))});
    // }
}
