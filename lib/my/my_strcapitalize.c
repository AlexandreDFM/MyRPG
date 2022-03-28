/*
** EPITECH PROJECT, 2021
** my_strcapitalize
** File description:
** Function that capitalizes the first letter of each word
*/

#include "my.h"

char *my_strcapitalize(char *str)
{
    int i = 1;
    my_strlowcase(str);
    if (str[i] >= 97 && str[i] <= 122)
        str[0] = str[0] - 32;
    while (str[i] != 0) {
        if (str[i - 1] >= 32 &&
        str[i - 1] <= 48 && str[i] > 96 && str[i] < 123) {
            str[i] = str[i] - 32;
        }
        i += 1;
    }
    return (str);
}
