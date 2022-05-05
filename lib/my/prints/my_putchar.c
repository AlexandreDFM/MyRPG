/*
** EPITECH PROJECT, 2021
** my_putchar
** File description:
** Putchar
*/

#include <unistd.h>
#include "../printf.h"

int my_putchar_disp(int file, char *c)
{
    write(file, c, 1);
    return 0;
}
