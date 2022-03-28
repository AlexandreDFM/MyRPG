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
        my_putchar('-');
        number = number * (-1);
    }
    if (number >= 10) {
        number2 = number % 10;
        number = number / 10;
        my_put_nbr(number);
        my_putchar(number2 + 48);
    } else {
        my_putchar(number + 48);
    }
    return (0);
}
