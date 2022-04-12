/*
** EPITECH PROJECT, 2022
** RedDungeon
** File description:
** main
*/

#include "dungeon.h"
#define MAP_SIZE 50
#define H_RATIO 0.45
#define W_RATIO 0.45

char **empty_map(int size)
{
    char **new = malloc(sizeof(char *) * (size + 1));
    new[size] = 0;
    for (int i = 0; i < size; i++) {
        new[i] = malloc(size + 1);
        memset(new[i], '.', size);
        new[i][size] = '\0';
    }
    return new;
}

void display_map(char **map)
{
    for (int y = 0; map[y] != 0; y++) {
        for (int x= 0; map[y][x] != '\0'; x++) {
            my_printf("%c", map[y][x]);
        }
        my_printf("\n");
    }
}

bsp *split_container(sfIntRect *main, int iter)
{
    bsp *root = malloc(sizeof(bsp));
    root->rect = main, root->left = 0, root->right = 0;
    if (iter != 0) {
        sfIntRect **lr = random_split(main);
        root->left = split_container(lr[0], iter - 1);
        root->right = split_container(lr[1], iter - 1);
        free(lr);
    }
    return root;
}

int random_btw(int min, int max)
{
    int mid = max / 2;
    return (rand() % (max - min + 1)) + min;
}

sfIntRect **random_split(sfIntRect *rect)
{
    sfIntRect **splits = malloc(sizeof(sfIntRect*) * 2);
    sfIntRect *left = malloc(sizeof(sfIntRect));
    sfIntRect *right = malloc(sizeof(sfIntRect));
    if (rand() % 2) {
        *left = (sfIntRect){rect->left, rect->top, random_btw(1, rect->width), rect->height};
        splits[0] = left;
        *right = (sfIntRect){rect->left + splits[0]->width, rect->top, rect->width - splits[0]->width, rect->height};
        splits[1] = right;
        float left_ratio = (float)left->width / (float)left->height;
        float right_ratio = (float)right->width / (float)right->height;
        if (left_ratio < W_RATIO || right_ratio < W_RATIO) {
            free(splits);
            free(left);
            free(right);
            return random_split(rect);
        }
    } else {
        *left = (sfIntRect){rect->left, rect->top, rect->width, random_btw(1, rect->height)};
        splits[0] = left;
        *right = (sfIntRect){rect->left, rect->top + splits[0]->height, rect->width, rect->height - splits[0]->height};
        splits[1] = right;
        float left_ratio = (float)left->height / (float)left->width;
        float right_ratio = (float)right->height / (float)right->width;
        if (left_ratio < H_RATIO || right_ratio < H_RATIO) {
            free(splits);
            free(left);
            free(right);
            return random_split(rect);
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
    sfIntRect room = {rect->left, rect->top, (float)rect->width / 1.5f, (float)rect->height / 1.5f};
    room.left += random_btw(0, (float)rect->width / 4.0f);
    room.top += random_btw(0, (float)rect->height / 4.0f);
    return room;
}

void populate_map(char ***map, bsp *tree, sfIntRect ***rects, int *count)
{
    if (tree) {
        if (is_leaf(tree)) {
            sfIntRect rect = generate_room(tree->rect);
            char rdm = '0' + rand() % 9;
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
    memset(new, 0, y + 2);
    for (int i = 0; i < y; i++) {
        new[i] = (*rects)[i];
    }
    new[y] = new_alloc;
    new[y + 1] = 0;
    *rects = new;
}

sfIntRect get_center(sfIntRect *rect)
{
    return (sfIntRect){rect->left + rect->width / 2, rect->top + rect->height / 2};
}

void get_paths(char ***map, bsp *tree)
{
    if (!tree->left || !tree->right)
        return;
    sfIntRect *rect = tree->left->rect;
    sfVector2i center_a = (sfVector2i){(float)rect->left + (float)rect->width / 2.0f, (float)rect->top + (float)rect->height / 2.0f};
    rect = tree->right->rect;
    sfVector2i center_b = (sfVector2i){(float)rect->left + (float)rect->width / 2.0f, (float)rect->top + (float)rect->height / 2.0f};

    int diff = center_a.x == center_b.x ? -1 : 1;
    int min = 0, max = 0;
    if (diff == 1) {
        min = center_a.x < center_b.x ? center_a.x : center_b.x;
        max = min == center_a.x ? center_b.x : center_a.x;
        for (int i = min; i < max; i++) {
            if ((*map)[center_a.y][i] == '.') {
                (*map)[center_a.y][i] = ' ';
            }		
        }
    } else {
        min = center_a.y < center_b.y ? center_a.y : center_b.y;
        max = min == center_a.y ? center_b.y : center_a.y;
        for (int i = min; i < max; i++) {
            if ((*map)[i][center_a.x] == '.') {
                (*map)[i][center_a.x] = ' ';
            }		
        }
    }
    
    get_paths(map, tree->left);
    get_paths(map, tree->right);
}

int is_leaf(bsp *tree) {
    if (!tree->left && !tree->right) {
        return 1;
    }
    return 0;
}

map_inf generate_map(int iter, sfImage *atlas)
{
    sfIntRect **rects = 0;
    sfIntRect **paths = 0;
    int count = 0; 
    char **map = empty_map(MAP_SIZE + 2);
    bsp *tree = build_bsp(MAP_SIZE, iter);
    populate_map(&map, tree, &rects, &count);
    get_paths(&map, tree);
    sfImage *img = generate_map_image(map, MAP_SIZE + 2, atlas);
    sfTexture *tex = sfTexture_createFromImage(img, NULL);
    sfImage_destroy(img);
    return (map_inf){tex, map, rects, count};
}
