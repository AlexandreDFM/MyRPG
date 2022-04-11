/*
** EPITECH PROJECT, 2021
** my_find_prime_sup
** File description:
** Returns the smallest prime of a number
*/

#include "my.h"

int my_find_prime_sup(int nb)
{
    int prime = nb;
    while (!my_is_prime(prime))
        prime += 1;
    return (prime);
}
