/*
** EPITECH PROJECT, 2021
** my_putstr
** File description:
** display str
*/

#include "../printf.h"

int my_putstrprintf(int file, char *str)
{
    int counter = 0;
    while (str[counter] != 0) {
        my_putchar_disp(file, &(str[counter]));
        counter = counter + 1;
    }
    return (0);
}
