/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** fill_map
*/

#include "dungeon.h"

void fill_map(sfIntRect rect, char ***map)
{
    for (int y = rect.top; y < rect.top + rect.height; y++) {
        for (int i = rect.left; i < rect.left + rect.width; i++) {
        (*map)[y][i] = ' ';
        }
    }
}

void populate_map(char ***map, bsp *tree, sfIntRect ***rects, int *count)
{
    if (tree) {
        if (is_leaf(tree)) {
            sfIntRect rect = generate_room(tree->rect);
            fill_map(rect, map);
            sfIntRect *malloced = malloc(sizeof(sfIntRect));
            *malloced = rect;
            append_list(rects, malloced);
            (*count)++;
        }
        populate_map(map, tree->left, rects, count);
        populate_map(map, tree->right, rects, count);
    }
}
