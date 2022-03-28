/*
** EPITECH PROJECT, 2021
** my_compute_power_rec
** File description:
** Returns the argument power
*/

#include "my.h"

int my_compute_power_rec(int nb, int p)
{
    if (p == 0 || nb == 1) {
        return (1);
    } else if (p < 0) {
        return (0);
    } else {
        return (nb * my_compute_power_rec(nb, p - 1));
    }
}
