/*
** EPITECH PROJECT, 2021
** my_str_isupper
** File description:
** Returns 1 if string contains only uppercase alphabetical characters
*/

#include "my.h"

int my_str_isupper(char const *str)
{
    int i = 0;
    while (str[i] != 0) {
        if (str[i] < 65 || str[i] > 90) {
            return (0);
        }
        i += 1;
    }
    return (1);
}
