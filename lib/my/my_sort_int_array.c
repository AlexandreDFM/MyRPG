/*
** EPITECH PROJECT, 2021
** my_sort_int_array
** File description:
** Sorts an integer array order
*/

#include "my.h"

void swap_numbers(int *array, int counter, int counter2)
{
    int a = 0;
    if (array[counter] > array[counter2]) {
        a = array[counter];
        array[counter] = array[counter2];
        array[counter2] = a;
    }
}

void my_sort_int_array(int *array, int size)
{
    for (int counter = 0; counter < size; ++counter){
        for (int counter2 = counter + 1; counter2 < size; ++counter2){
            swap_numbers(array, counter, counter2);
        }
    }
}
