/*
** EPITECH PROJECT, 2021
** my_putstr
** File description:
** display str
*/

#include "../printf.h"

int my_putstr(char const *str)
{
    int counter = 0;
    while (str[counter] != 0) {
        my_putchar(str[counter]);
        counter = counter + 1;
    }
    return (0);
}
