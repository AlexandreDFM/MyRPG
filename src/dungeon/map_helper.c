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

sfIntRect generate_room(sfIntRect *rect)
{
    sfIntRect room = {rect->left, rect->top,
        (float)rect->width / 1.5f, (float)rect->height / 1.5f};
    room.left += rdm_btw(0, (float)rect->width / 4.0f);
    room.top += rdm_btw(0, (float)rect->height / 4.0f);
    return room;
}
