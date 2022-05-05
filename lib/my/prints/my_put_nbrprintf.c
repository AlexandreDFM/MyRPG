/*
** EPITECH PROJECT, 2021
** my_put_nbr
** File description:
** Display all the possible values of a int
*/

#include "../printf.h"

int my_put_nbrprintf(int file, int number)
{
    int number2;
    if (number < 0) {
        int minus = '-';
        my_putchar_disp(file, (char*)(&minus));
        number = number * (-1);
    }
    if (number >= 10) {
        number2 = number % 10;
        number = number / 10;
        my_put_nbrprintf(file, number);
        number2 += '0';
        my_putchar_disp(file, (char*)(&number2));
    } else {
        number += '0';
        my_putchar_disp(file, (char*)(&number));
    }
    return (0);
}
