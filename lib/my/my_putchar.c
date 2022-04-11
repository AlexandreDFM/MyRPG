/*
** EPITECH PROJECT, 2021
** my_putchar
** File description:
** Putchar
*/

#include <unistd.h>
#include "my.h"

void my_putchar(char c)
{
    write(1, &c, 1);
}
