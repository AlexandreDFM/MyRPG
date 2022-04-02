/*
** EPITECH PROJECT, 2021
** my_atoi
** File description:
** my_atoi
*/

#include "my.h"

int my_atoi(char const *str)
{
    int i = 0, result = 0, check = 1;
    if (str[0] == '\0' || (str[0] > '9' && str[0] < '0'))
        return (0);
    if (str[0] == '-' && (str[1] <= '9' && str[1] >= '0')) {
        check = -1;
        i++;
    }
    for (; str[i] != '\0' && (str[i] <= '9' && str[i] >= '0'); i++) {
        result += str[i] - '0';
        if (str[i + 1] <= '9' && str[i + 1] >= '0') result *= 10;
    }
    return (result * check);
}
