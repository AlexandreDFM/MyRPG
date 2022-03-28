/*
** EPITECH PROJECT, 2021
** my_str_isprintable
** File description:
** Returns 1 if string only contains printable characters
*/

#include "my.h"

int my_str_isprintable(char const *str)
{
    int i = 0;
    while (str[i] != 0) {
        if (str[i] < 32 || str[i] == 127) {
            return (0);
        }
        i += 1;
    }
    return (1);
}
