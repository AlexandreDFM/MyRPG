/*
** EPITECH PROJECT, 2022
** RedDungeon
** File description:
** main
*/

#include "dungeon.h"

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
