/*
** EPITECH PROJECT, 2021
** my_strncat
** File description:
** Function that concatenates n characters
*/

#include "my.h"

char *my_strncat(char *dest, char const *src, int nb)
{
    int i = 0;
    int counter = my_strlen(dest);
    while (i < nb && src[i] != 0) {
        dest[counter + i] = src[i];
        i += 1;
    }
    dest[counter + i] = 0;
    return (dest);
}
