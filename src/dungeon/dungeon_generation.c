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
    win->dungeon.inf = generate_map(3, img); sfImage_destroy(img);
    if (win->net->is_multi) {
        sfSprite *sp = win->dungeon.inf->sp;
        win->dungeon.inf->sp = 0;
        add_ord(DUNGEONSYNC, win->dungeon.inf, sizeof(win->dungeon.inf),
            win->net->packet);
        add_ord(APPEND, &id, sizeof(int), win->net->packet);
        win->dungeon.inf->sp = sp;
    } win->dungeon.in = 1;
    map_inf *i = win->dungeon.inf;
    sfVector2i pos = global_to_local(i->starting_pos);
    pos.x += 3;
    create_enemy(win, &win->dungeon, pos);
}
