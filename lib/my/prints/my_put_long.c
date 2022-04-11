/*
** EPITECH PROJECT, 2021
** my_put_long
** File description:
** my_put_long
*/

#include "../printf.h"

int my_put_long(long long int number)
{
    long long int number2 = 0;
    if (number < 0) {
        my_putchar('-');
        number = number * (-1);
    }
    if (number >= 10) {
        number2 = number % 10;
        number = number / 10;
        my_put_long(number);
        my_putchar(number2 + 48);
    } else {
        my_putchar(number + 48);
    }
    return (0);
}
