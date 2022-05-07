/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** bsp
*/

#include "dungeon.h"

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

bsp *build_bsp(int size, int iter)
{
    sfIntRect *rect = malloc(sizeof(sfIntRect));
    *rect = (sfIntRect){2, 1, size, size};
    return split_container(rect, iter);
}

int is_leaf(bsp *tree)
{
    if (!tree->left && !tree->right) {
        return 1;
    }
    return 0;
}
