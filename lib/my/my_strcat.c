/*
** EPITECH PROJECT, 2021
** my_strcat
** File description:
** Cat two strings*
*/

#include "my.h"

char *my_strcat(char *dest, const char *src)
{
    int dest_length = my_strlen(dest);
    int i;
    for (i = 0; src[i] != '\0'; i++) {
        dest[dest_length + i] = src[i];
    }
    dest[dest_length + i] = '\0';

    return (dest);
}
