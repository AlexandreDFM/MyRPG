/*
** EPITECH PROJECT, 2021
** my_putstr
** File description:
** display str
*/

#include "my.h"
#include <unistd.h>

int my_putstr(char const *str)
{
    write(1, str, my_strlen(str));
}
