/*
** EPITECH PROJECT, 2021
** my_revstr
** File description:
** Reverse a string
*/

#include "my.h"

char *my_revstr(char *str)
{
    char temp;
    int i = my_strlen(str) - 1;
    int counter = 0;
    while (counter < i) {
        temp = str[i];
        str[i] = str[counter];
        str[counter] = temp;
        i -= 1;
        counter += 1;
    }
    return (str);
}
