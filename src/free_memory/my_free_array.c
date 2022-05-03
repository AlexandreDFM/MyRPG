/*
** EPITECH PROJECT, 2022
** my_free_array
** File description:
** Free double array function
*/

#include "rpg.h"

void my_free_array(char **array)
{
    for (int i = 0; array[i]; i++) {
        free(array[i]);
    }
    free(array);
}
