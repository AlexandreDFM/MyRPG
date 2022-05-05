/*
** EPITECH PROJECT, 2021
** my_put_unsigned
** File description:
** Put an unsigned number
*/

#include "../printf.h"

int my_put_short_unsigned(short int number)
{
    int number2;
    if (number < 0) {
        int minus = '-';
        my_putchar_disp((char*)(&minus), 0);
        number = number * (-1);
    }
    if (number >= 10) {
        number2 = number % 10;
        number = number / 10;
        my_put_nbr(number);
        number2 += '0';
        my_putchar_disp((char*)(&number2), 0);
    } else {
        number += '0';
        my_putchar_disp((char*)(&number), 0);
    }
    return (0);
}
