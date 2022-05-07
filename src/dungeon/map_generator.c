/*
** EPITECH PROJECT, 2022
** RedDungeon
** File description:
** main
*/

#include "dungeon.h"

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

int paths2(int min, int max, char ***map, sfVector2i center_a)
{
    int out = 1;
    for (int i = min; i < max; i++) {
        if ((*map)[center_a.y - 1][i] == '.') {
            (*map)[center_a.y - 1][i - 1] = out ? 'E' :
            (*map)[center_a.y - 1][i - 1];
            (*map)[center_a.y - 1][i] = 'T';
            out = 0;
        } else if (!out) {
            (*map)[center_a.y - 1][i] = 'E';
            out = 1;
        }
    }
    return out;
}

int paths3(int out, char ***map, sfVector2i center_a, sfVector2i center_b)
{
    int min = center_a.y < center_b.y ? center_a.y : center_b.y;
    int max = min == center_a.y ? center_b.y : center_a.y;
    for (int i = min; i < max; i++) {
        if ((*map)[i][center_a.x] == '.') {
                (*map)[i - 1][center_a.x - 1] = out ? 'E' :
                (*map)[i - 1][center_a.x - 1];
            (*map)[i][center_a.x - 1] = 'T';
            out = 0;
        } else if ((*map)[i][center_a.x - 1] == ' ') {
                (*map)[i - 1][center_a.x - 1] = !out ? 'E' :
                (*map)[i - 1][center_a.x - 1];
            out = 1;
        }
    }
    return out;
}

void get_paths(char ***map, bsp *tree)
{
    if (!tree->left || !tree->right) return;
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
        out = paths2(min, max, map, center_a);
    } else {
        out = paths3(out, map, center_a, center_b);
    }
    get_paths(map, tree->left); get_paths(map, tree->right);
    clean_map(map);
}
