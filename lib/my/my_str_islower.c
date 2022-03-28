/*
** EPITECH PROJECT, 2021
** my_str_islower
** File description:
** Returns 1 if string only contains lowercase alphabetical
*/

#include "my.h"

int my_str_islower(char const *str)
{
    int i = 0;
    while (str[i] != 0) {
        if (str[i] >= 97 && str[i] <= 122) {
            i += 1;
        } else {
            return (0);
        }
    }
    return (1);
}
