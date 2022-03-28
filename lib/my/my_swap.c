/*
** EPITECH PROJECT, 2021
** my_swap
** File description:
** swap int a and int b
*/

#include "my.h"

void my_swap(int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
