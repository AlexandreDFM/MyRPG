/*
** EPITECH PROJECT, 2021
** my_itoa
** File description:
** my_itoa
*/

#include "rpg.h"

int get_int_len(long long int nbr)
{
    int i = 0;
    for (; nbr > 9; i++) {
        nbr /= 10;
    }
    return i + 1;
}

char *my_itoa(int num)
{
    char *str = malloc(sizeof(char) * get_int_len(num) + 4);
    int i = 0, is_negative = 0;
    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    while (num != 0) {
        int rem = num % 10;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num = num / 10;
    }
    if (is_negative) str[i++] = '-';
    str[i] = '\0';
    my_revstr(str);
    return str;
}
