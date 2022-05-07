/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_map
*/

#include "dungeon.h"

char **empty_map(int size)
{
    char **new = malloc(sizeof(char *) * (size + 1));
    new[size] = 0;
    for (int i = 0; i < size; i++) {
        new[i] = malloc(size + 1);
        my_memset(new[i], '.', size);
        new[i][size] = '\0';
    }
    return new;
}

map_inf *generate_map(int iter, sfImage *atlas)
{
    sfIntRect **rects = 0;
    int count = 0;
    char **map = empty_map(MAP_SIZE + 2);
    bsp *tree = build_bsp(MAP_SIZE, iter);
    populate_map(&map, tree, &rects, &count);
    get_paths(&map, tree);
    for (int i = 0; map[i] != NULL; i++) printf("%s\n", map[i]);
    sfImage *img = generate_map_image(map, MAP_SIZE + 2, atlas);
    sfTexture *tex = my_texture_from_image(img, NULL);
    sfSprite *sp = sfSprite_create();
    sfSprite_setTexture(sp, tex, sfFalse);
    sfImage_destroy(img);
    map_inf *inf = malloc(sizeof(map_inf));
<<<<<<< HEAD
    // inf->pos = get_random_position(rects, count, &map);
=======
    inf->starting_pos = get_random_position(rects, count);
    sfVector2i end = global_to_local(get_random_position(rects, count));
    map[end.y][end.x] = 'F';
>>>>>>> 80c9d694838da08c2dbe1f89da8dfd86f546f5d2
    inf->map = map; inf->sp = sp; inf->rooms = rects; inf->nbr_rooms = count;
    return inf;
}

sfIntRect generate_room(sfIntRect *rect)
{
    sfIntRect room = {rect->left, rect->top,
        (float)rect->width / 1.5f, (float)rect->height / 1.5f};
    room.left += rdm_btw(0, (float)rect->width / 4.0f);
    room.top += rdm_btw(0, (float)rect->height / 4.0f);
    return room;
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
    *l = (sfIntRect){r->left, r->top, r->width, rdm_btw(2, r->height - 2)};
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
