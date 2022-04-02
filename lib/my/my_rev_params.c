/*
** EPITECH PROJECT, 2021
** my_rev_params
** File description:
** Display argument receveid on the command line
*/

#include "my.h"

int my_rev_params(int argc, char **argv)
{
    for (int counter = argc - 1; counter >= 0; counter--) {
        my_putstr(argv[counter]);
        my_putchar('\n');
    }
    return (0);
}
