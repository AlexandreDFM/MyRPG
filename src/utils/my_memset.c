/*
** EPITECH PROJECT, 2021
** My_memset
** File description:
** Reset memory with given value
*/

#include "rpg.h"

void *my_memset(void *dest, int value, int length)
{
    char *ptr = dest;
    while (length-- > 0) {
        *ptr++ = value;
    }
    return dest;
}
