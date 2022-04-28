/*
** EPITECH PROJECT, 2022
** my_slice_array
** File description:
** Function to slice array
*/

#include "rpg.h"

char *left_slice(char *strslice, char *new_array, int i, int j)
{
    for (; strslice[i] != '\0'; i++, j++)
        new_array[j] = strslice[i];
    new_array[j] = '\0';
    return new_array;
}

char *right_slice(char *strslice, char *new_array, int i, int j)
{
    for (; strslice[j] < my_strlen(strslice) - i; j++)
        new_array[j] = strslice[j];
    new_array[j] = '\0';
    return new_array;
}

char *my_slice_array(int direction, char *strslice, int nbslice)
{
    int i = nbslice, j = 0;
    char *array = malloc(sizeof(char) * (my_strlen(strslice) - nbslice + 1));
    if (direction == 0) {
        return left_slice(strslice, array, i, j);
    } else if (direction == 1) {
        return right_slice(strslice, array, i, j);
    } else {
        return NULL;
    }
}
