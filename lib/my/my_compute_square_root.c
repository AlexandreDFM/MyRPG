/*
** EPITECH PROJECT, 2021
** my_compute_square_root
** File description:
** Square Root
*/

#include "my.h"

int my_compute_square_root(int nb)
{
    int sqrt = nb / 2;
    int temp = 0;
    if (nb < 0)
        return (0);
    else if (nb == 1)
        return (1);
    while (sqrt != temp) {
        temp = sqrt;
        sqrt = (nb / temp + temp) / 2;
        if (sqrt > temp)
            return (0);
    }
    if (sqrt * sqrt == nb)
        return (sqrt);
    else
        return (0);
}
