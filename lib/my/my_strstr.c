/*
** EPITECH PROJECT, 2021
** my_strstr
** File description:
** Search a substring in a fullstring
*/

#include "my.h"

char *my_strstr(char *str, char const *to_find)
{
    int i = 0;
    int i2 = 0;
    int findlen = my_strlen(to_find);
    while (str[i] != '\0') {
        if (str[i] == to_find[i2] && i2 == findlen - 1)
            return (str);
        else if (str[i] == to_find[i2] && i2 < findlen)
            i2 = i2 + 1;
        else
            i2 = 0;
        i = i + 1;
    }
    return (0);
}
