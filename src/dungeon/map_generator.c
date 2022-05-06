/*
** EPITECH PROJECT, 2022
** RedDungeon
** File description:
** main
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

bsp *split_container(sfIntRect *main, int iter)
{
    bsp *root = malloc(sizeof(bsp));
    root->rect = main, root->left = 0, root->right = 0;
    if (iter != 0) {
        sfIntRect **lr = random_split(main, 1000);
        if (lr) {
            root->left = split_container(lr[0], iter - 1);
            root->right = split_container(lr[1], iter - 1);
            free(lr);
        }
    }
    return root;
}

int rdm_btw(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

void fill_lre(sfIntRect *l, sfIntRect *re, sfIntRect *r, sfIntRect** splits)
{
    l->left = r->left; l->top = r->top; l->width = rdm_btw(2, r->width - 2);
    l->height = r->height;
    splits[0] = l;
    re->left = r->left + splits[0]->width; re->top = r->top;
    re->width = r->width - splits[0]->width; re->height = r->height;
    splits[1] = re;
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

bsp *build_bsp(int size, int iter)
{
    sfIntRect *rect = malloc(sizeof(sfIntRect));
    *rect = (sfIntRect){2, 1, size, size};
    return split_container(rect, iter);
}

sfIntRect generate_room(sfIntRect *rect)
{
    sfIntRect room = {rect->left, rect->top,
        (float)rect->width / 1.5f, (float)rect->height / 1.5f};
    room.left += rdm_btw(0, (float)rect->width / 4.0f);
    room.top += rdm_btw(0, (float)rect->height / 4.0f);
    return room;
}

void populate_map(char ***map, bsp *tree, sfIntRect ***rects, int *count)
{
    if (tree) {
        if (is_leaf(tree)) {
            sfIntRect rect = generate_room(tree->rect);
            for (int y = rect.top; y < rect.top + rect.height; y++) {
                for (int i = rect.left; i < rect.left + rect.width; i++) {
                    (*map)[y][i] = ' ';
                }
            }
            sfIntRect *malloced = malloc(sizeof(sfIntRect));
            *malloced = rect;
            append_list(rects, malloced);
            (*count)++;
        }
        populate_map(map, tree->left, rects, count);
        populate_map(map, tree->right, rects, count);
    }
}

void free_list(sfIntRect **rects) {
    for (int i = 0; rects[i]; i++) {
        free(rects[i]);
    }
    free(rects);
}

void append_list(sfIntRect ***rects, sfIntRect *new_alloc)
{
    int y = 0;
    for (; *rects && (*rects)[y]; y++);
    sfIntRect **new = malloc(sizeof(sfIntRect*) * (y + 2));
    my_memset(new, 0, y + 2);
    for (int i = 0; i < y; i++) {
        new[i] = (*rects)[i];
    }
    new[y] = new_alloc;
    new[y + 1] = 0;
    *rects = new;
}

sfIntRect get_center(sfIntRect *rect)
{
    return (sfIntRect){rect->left + rect->width / 2,
        rect->top + rect->height / 2};
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

void get_paths(char ***map, bsp *tree)
{
    if (!tree->left || !tree->right)
        return;
    sfIntRect *r = tree->left->rect;
    sfVector2i center_a = (sfVector2i){(float)r->left + (float)r->width / 2.0f,
        (float)r->top + (float)r->height / 2.0f};
    r = tree->right->rect;
    sfVector2i center_b = (sfVector2i){(float)r->left + (float)r->width / 2.0f,
        (float)r->top + (float)r->height / 2.0f};
    int diff = center_a.x == center_b.x ? -1 : 1;
    int min = 0, max = 0, out = 1;
    if (diff == 1) {
        min = center_a.x < center_b.x ? center_a.x : center_b.x;
        max = min == center_a.x ? center_b.x : center_a.x;
        for (int i = min; i < max; i++) {
            if ((*map)[center_a.y - 1][i] == '.') {
                if (out)
                    (*map)[center_a.y - 1][i - 1] = 'E';
                (*map)[center_a.y - 1][i] = 'T';
                out = 0;
            } else if (!out) {
                (*map)[center_a.y - 1][i] = 'E';
                out = 1;
            }
        }
    } else {
        min = center_a.y < center_b.y ? center_a.y : center_b.y;
        max = min == center_a.y ? center_b.y : center_a.y;
        for (int i = min; i < max; i++) {
            if ((*map)[i][center_a.x] == '.') {
                if (out)
                    (*map)[i - 1][center_a.x - 1] = 'E';
                (*map)[i][center_a.x - 1] = 'T';
                out = 0;
            } else if ((*map)[i][center_a.x - 1] == ' ') {
                if (!out) {
                    (*map)[i][center_a.x - 1] = 'E';
                }
                out = 1;
            }
        }
    }
    get_paths(map, tree->left);
    get_paths(map, tree->right);
    clean_map(map);
}

int is_leaf(bsp *tree) {
    if (!tree->left && !tree->right) {
        return 1;
    }
    return 0;
}

map_inf *generate_map(int iter, sfImage *atlas)
{
    sfIntRect **rects = 0;
    int count = 0;
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
    inf->pos = get_random_position(rects, count, &map);
    inf->map = map; inf->sp = sp; inf->rooms = rects; inf->nbr_rooms = count;
    return inf;
}
