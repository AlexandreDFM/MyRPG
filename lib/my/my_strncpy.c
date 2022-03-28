/*
** EPITECH PROJECT, 2021
** my_strncpy
** File description:
** Copies n characters from a string into another
*/

#include "my.h"

char *my_strncpy(char *dest, char const *src, int n)
{
    int i = 0;
    while (src[i] != 0 && i < n) {
        dest[i] = src[i];
        i += 1;
    }
    while (i < n) {
        dest[i] = '\0';
        i += 1;
    }
    return (dest);
}
