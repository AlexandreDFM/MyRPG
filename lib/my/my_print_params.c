/*
** EPITECH PROJECT, 2021
** my_print_params
** File description:
** Display argument receveid on the command line
*/

#include "my.h"

int my_print_params(int argc, char **argv)
{
    int counter = 0;
    int i = 0;
    while (argv[counter] != 0) {
        i = 0;
        while (argv[counter][i] != '\0') {
            my_putchar(argv[counter][i]);
            i += 1;
        }
        my_putchar('\n');
        counter += 1;
    }
    return (0);
}
