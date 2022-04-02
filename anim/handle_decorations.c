/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** handle_decorations
*/

#include "rpg.h"

void place_decorations(char *line, sfImage *atlas, char **csv, list **l)
{
    char **arr = my_strtwa(line, ";\n");
    int len = 0;
    for (; arr[len]; len++);
    len = len / 3.0f;
    for (int i = 0; i < len; i++) {
        create_static_anim(atlas, arr[i * 3], l, csv);
        sfVector2f p = (sfVector2f){my_atoi(arr[i * 3 + 1]),
        my_atoi(arr[i * 3 + 2])};
        sfSprite_setPosition(((entity*)(*l)->data)->sp, p);
    }
}
