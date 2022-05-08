/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_map
*/

#include "dungeon.h"

void create_exit(sfImage *atlas, char ***map, map_inf *inf, sfVector2f rdm)
{
    sfVector2i end = global_to_local(rdm);
    (*map)[end.y][end.x] = 'F';
    if (!inf->stairs) {
        sfIntRect r = (sfIntRect){790, 1157, 24, 24};
        sfTexture *tex = sfTexture_createFromImage(atlas, &r);
        sfSprite *stairs = sfSprite_create();
        sfSprite_setTexture(stairs, tex, sfFalse);
        sfSprite_setOrigin(stairs, (sfVector2f){12, 12});
        inf->stairs = stairs;
    }
    sfSprite_setPosition(inf->stairs, rdm);
}

map_inf *generate_map(int iter, sfImage *atlas, sfImage *atlas2)
{
    sfIntRect **rects = 0; int count = 0;
    char **map = empty_map(MAP_SIZE + 2);
    bsp *tree = build_bsp(MAP_SIZE, iter);
    populate_map(&map, tree, &rects, &count);
    get_paths(&map, tree);
    sfImage *img = generate_map_image(map, MAP_SIZE + 2, atlas);
    sfTexture *tex = my_texture_from_image(img, NULL);
    sfSprite *sp = sfSprite_create();
    sfSprite_setTexture(sp, tex, sfFalse);
    sfImage_destroy(img);
    map_inf *inf = malloc(sizeof(map_inf));
    inf->starting_pos = get_random_position(rects, count); inf->stairs = 0;
    create_exit(atlas2, &map, inf, get_random_position(rects, count));
    inf->map = map; inf->sp = sp; inf->rooms = rects; inf->nbr_rooms = count;
    return inf;
}

sfIntRect **random_split(sfIntRect *r, int iter)
{
    if (!iter) return 0;
    sfIntRect **splits = malloc(sizeof(sfIntRect*) * 2);
    sfIntRect *l = malloc(sizeof(sfIntRect)), *re = malloc(sizeof(sfIntRect));
    if (rand() % 2) {
        fill_lre(l, re, r, splits);
        float lr = (float)l->width / (float)l->height;
        float rr = (float)re->width / (float)re->height;
        if (!(lr < W_RATIO || rr < W_RATIO)) return splits;
        free(splits); free(l); free(re); return random_split(r, iter--);
    }
    *l = (sfIntRect){r->left, r->top, r->width, rdm_btw(3, r->height - 3)};
    splits[0] = l;
    *re = (sfIntRect){r->left, r->top + splits[0]->height, r->width,
        r->height - splits[0]->height}; splits[1] = re;
    float left_ratio = (float)l->height / (float)l->width;
    float right_ratio = (float)re->height / (float)re->width;
    if (!(left_ratio < H_RATIO || right_ratio < H_RATIO)) return splits;
    free(splits); free(l); free(re); return random_split(r, iter--);
}

void clean_map(char ***mapref)
{
    char **map = *mapref;
    for (int y = 0; map[y]; y++) {
        for (int x = 0; map[y][x] != '\0'; x++) {
            char c = map[y][x];
            map[y][x] = c == 'T' ? ' ' : c;
        }
    }
}
