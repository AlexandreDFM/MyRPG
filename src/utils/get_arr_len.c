/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** get_arr_len
*/

#include "rpg.h"

int get_arr_len(char **arr)
{
    int i = 0;
    while (arr[i] != NULL)
        i++;
    return i - 1;
}
