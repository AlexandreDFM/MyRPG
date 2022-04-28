/*
** EPITECH PROJECT, 2022
** B-CPE-200-NCE-2-1-lemin-antoine.frankel
** File description:
** my_strdup_to_char
*/

#include "rpg.h"

int test_delim(char c, char *delim)
{
    for (int i = 0; delim[i] != '\0'; i++) {
        if (c == delim[i]) {
            return 1;
        }
    }
    return 0;
}

char *my_strdup_to_char(char *src, char *delim)
{
    if (!src) return NULL;
    int i = 0;
    for (; src[i] != '\0' && test_delim(src[i], delim) == 0; i++);
    char *dest = malloc(sizeof(char) * (i + 1));
    for (int j = 0; j < i; j++) dest[j] = src[j];
    dest[i] = '\0';
    return dest;
}

char *my_strdup_value(char *src, int value)
{
    if (!src) return NULL;
    int i = 0;
    for (; src[i] != '\0' && i < value; i++);
    char *dest = malloc(sizeof(char) * (i + 1));
    for (int j = 0; j < i; j++) dest[j] = src[j];
    dest[i] = '\0';
    return dest;
}
