/*
** EPITECH PROJECT, 2021
** my_isneg
** File description:
** Return N for negative and P for positive or null.
*/

#include "my.h"

int my_isneg(int i)
{
    if (i >= 0) {
        my_putchar('P');
    } else {
        my_putchar('N');
    }
    return (0);
}
