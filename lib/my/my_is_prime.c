/*
** EPITECH PROJECT, 2021
** my_is_prime
** File description:
** Return if the number is a prime
*/

#include "my.h"

int my_is_prime(int nb)
{
    int counter = 2;
    if (nb <= 1) {
        return (0);
    }
    while (counter <= nb / 2) {
        if (nb % counter == 0) {
            return (0);
        }
        counter += 1;
    }
    return (1);
}
