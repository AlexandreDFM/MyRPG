/*
** EPITECH PROJECT, 2021
** my_str_isnum
** File description:
** Returns 1 if string only contains digits and 0
*/

#include "my.h"

int my_str_isnum(char const *str)
{
    int i = 0;
    while (str[i] != 0) {
        if (str[i] < 48 || str[i] > 57) {
            return (0);
        }
        i += 1;
    }
    return (1);
}
