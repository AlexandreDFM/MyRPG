/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** rect_utils
*/

#include "dungeon.h"

sfIntRect get_center(sfIntRect *rect)
{
    return (sfIntRect){rect->left + rect->width / 2,
        rect->top + rect->height / 2};
}

void free_list(sfIntRect **rects)
{
    for (int i = 0; rects[i]; i++) {
        free(rects[i]);
    }
    free(rects);
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
