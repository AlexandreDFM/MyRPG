/*
** EPITECH PROJECT, 2021
** my_put_nbr_oct
** File description:
** Put nbr Oct Mod
*/

#include "../printf.h"

int my_putnbr_oct(int nbr)
{
    char *base = "01234567";
    int size = 0;
    int mod = nbr;
    while (base[size] != '\0')
        size++;
    if (size <= 1)
        return (nbr);
    mod %= size;
    if (mod < 0)
        mod = -mod;
    if (nbr / size == 0) {
        if (nbr < 0)
            my_putchar('-');
        my_putchar(base[mod]);
        return (nbr);
    }
    my_putnbr_oct(nbr / size);
    my_putchar(base[mod]);
    return (nbr);
}
