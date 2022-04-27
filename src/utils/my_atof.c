/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** my_atof
*/

#include "rpg.h"

float my_atof(char *number)
{
    int sign = number[0] == '-' ? -1 : 1;
    float nbr = 0.0f;
    int nbr_comma = 0;
    int power = 0;
    int len = my_strlen(number) - 1;
    for (int i = len; i >= 0; i--, nbr_comma++, power++) {
        if (number[i] == '-') continue;
        if (number[i] == ',' || number[i] == '.') {
            nbr /= pow(10.0f, nbr_comma);
            power = -1;
            continue;
        }
        nbr += (number[i] - '0') * pow(10, power);
    }
    return (nbr * sign);
}
