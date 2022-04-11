/*
** EPITECH PROJECT, 2021
** my_strdup
** File description:
** my_strdup
*/

#include "rpg.h"
#include <stdlib.h>

char *my_strdup(char *src)
{
    if (!src) return 0;
    int length = my_strlen(src);
    char *out = malloc(sizeof(src) * (length + 2));

    my_strcpy(out, src);
    return out;
}
