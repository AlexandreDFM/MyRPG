/*
** EPITECH PROJECT, 2021
** my_putnbr.c
** File description:
** Return a number of a string
*/

#include "my.h"

int is_nbr(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    else
        return (0);
}

int is_add_sub(char c)
{
    if (c == '-' || c == '+')
        return (1);
    else
        return (0);
}

int my_getnbr(char const *str)
{
    int nb = 0;
    int counter = 0;
    int neg = 1;
    while (is_add_sub(str[counter]) == 1) {
        counter = counter + 1;
    }
    if (str[counter - 1] == '-')
        neg = -1;
    while (is_nbr(str[counter]) == 1) {
        if (nb < 0)
            return (0);
        nb = ((nb * 10) + (str[counter] - '0'));
        counter = counter + 1;
    }
    return (nb * neg);
}
