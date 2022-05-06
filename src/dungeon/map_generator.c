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

sfIntRect **random_split(sfIntRect *r, int iter)
{
    if (!iter) return 0;
    sfIntRect **splits = malloc(sizeof(sfIntRect*) * 2);
    sfIntRect *l = malloc(sizeof(sfIntRect)), *re = malloc(sizeof(sfIntRect));
    if (rand() % 2) {
        *l = (sfIntRect){r->left, r->top, rdm_btw(2, r->width - 2), r->height};
        splits[0] = l;
        *re = (sfIntRect){r->left + splits[0]->width, r->top,
            r->width - splits[0]->width, r->height};
        splits[1] = re;
        float left_ratio = (float)l->width / (float)l->height;
        float right_ratio = (float)re->width / (float)re->height;
        if (left_ratio < W_RATIO || right_ratio < W_RATIO) {
            free(splits);
            free(l);
            free(re);
            return random_split(r, iter--);
        }
    } else {
        *l = (sfIntRect){r->left, r->top, r->width, rdm_btw(2, r->height - 2)};
        splits[0] = l;
        *re = (sfIntRect){r->left, r->top + splits[0]->height, r->width,
            r->height - splits[0]->height};
        splits[1] = re;
        float left_ratio = (float)l->height / (float)l->width;
        float right_ratio = (float)re->height / (float)re->width;
        if (left_ratio < H_RATIO || right_ratio < H_RATIO) {
            free(splits);
            free(l);
            free(re);
            return random_split(r, iter--);
        }
    }
    return splits;
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
    if (tree && is_leaf(tree)) return;
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
    populate_map(map, tree->left, rects, count);
    populate_map(map, tree->right, rects, count);
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

void is_diff(char ***map, sfVector2i center_a, sfVector2i center_b)
{
    int out = 1;
    int min = center_a.x < center_b.x ? center_a.x : center_b.x;
    int max = min == center_a.x ? center_b.x : center_a.x;
    for (int i = min; i < max; i++) {
        char *line = (*map)[center_a.y - 1];
        if (line[i] == '.') {
            line[i - 1] = out ? 'E' : line[i - 1];
            line[i] = 'T';
            out = 0;
        } else if (!out) {
            line[i] = 'E';
            out = 1;
        }
    }
}

void is_not_diff(char ***map, sfVector2i center_a, sfVector2i center_b)
{
    int out = 1;
    int min = center_a.y < center_b.y ? center_a.y : center_b.y;
    int max = min == center_a.y ? center_b.y : center_a.y;
    for (int i = min; i < max; i++) {
        char *pl = (*map)[i];
        if ((*map)[i][center_a.x] == '.') {
            char *line = (*map)[i - 1];
            line[center_a.x - 1] = out ? 'E' : line[center_a.x - 1];
            (*map)[i][center_a.x - 1] = 'T';
            out = 0;
        } else if (pl[center_a.x - 1] == ' ') {
            pl[center_a.x - 1] = !out ? 'E' : pl[center_a.x - 1];
            out = 1;
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
    if (diff == 1) {
        is_diff(map, center_a, center_b);
    } else {
        is_not_diff(map, center_a, center_b);
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
