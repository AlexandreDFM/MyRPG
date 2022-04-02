/*
** EPITECH PROJECT, 2021
** my_strupcase
** File description:
** Puts every letter of every word in it in uppercase
*/

#include "my.h"

char *my_strupcase(char *str)
{
    int i = 0;
    while (str[i] != 0) {
        if (str[i] >= 97 && str[i] <= 122) {
            str[i] = str[i] - 32;
        }
        i += 1;
    }
    return (str);
}
