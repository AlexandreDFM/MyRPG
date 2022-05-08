/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** get_item_sprite
*/

#include "rpg.h"

sfSprite *get_item_sprite(int id, wininf *inf, player *p, int type)
{
    sfSprite *sp = sfSprite_create();
    char **arr = my_strtwa(inf->atlases.item_sprites[id], ";\n");
    sfIntRect r = (sfIntRect){my_atoi(arr[1]), my_atoi(arr[2]),
    my_atoi(arr[3]), my_atoi(arr[4])};
    sfTexture *tex = sfTexture_createFromImage(inf->atlases.atlas, &r);
    sfSprite_setTexture(sp, tex, sfFalse);
    sfSprite_setOrigin(sp, (sfVector2f){r.width / 2, r.height / 2});
    if (type) {
        sfVector2f pos = sfSprite_getPosition(p->test);
        sfVector2i loc = global_to_local(pos);
        sfSprite_setPosition(sp, get_valid_drop(loc, inf));
    }
    my_free_array(arr);
    return sp;
}
