/*
** EPITECH PROJECT, 2021
** my_put_unsigned
** File description:
** Put an unsigned number
*/

#include "../printf.h"

int my_put_unsigned(unsigned int number)
{
    int number2;
    if (number < 0) {
        char minus = '-';
        my_putchar_disp(0, &minus);
        number = number * (-1);
    }
    if (number >= 10) {
        number2 = number % 10;
        number = number / 10;
        my_put_nbrprintf(0, number);
        number2 += '0';
        my_putchar_disp(0, (char *)(&number2));
    } else {
        number += '0';
        my_putchar_disp(0, (char *)(&number));
    }
    return (0);
}
