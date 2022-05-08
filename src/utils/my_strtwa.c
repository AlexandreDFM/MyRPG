/*
** EPITECH PROJECT, 2022
** my_strtwa
** File description:
** Function to reproduce fekjlfzejp but output is double array
*/

#include "rpg.h"

int test_lim(char c, char *limit)
{
    for (int i = 0; limit[i] != '\0'; i++) {
        if (c == limit[i]) {
            return 1;
        }
    }
    return 0;
}

int nb_not_valid(char const *str, char *limit)
{
    int nby = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (test_lim(str[i], limit))
            nby += 1;
    }
    return nby;
}

char **my_alloc_array(char const *str, char *limit, char **dest)
{
    int nby = 0, nbx = 0;
    int len = my_strlen(str);
    for (int nbc = 0; nbc < len; nbc++, nbx++) {
        if (test_lim(str[nbc], limit)) {
            dest[nby] = malloc(sizeof(char) * (nbx + 1));
            dest[nby][nbx] = '\0';
            nby += 1, nbx = 0, nbc++;
        }
        if (nbc >= len) break;
    }
    return dest;
}

char **my_strtwa(char const *str, char *limit)
{
    int nbmax = (nb_not_valid(str, limit)), nby = 0, nbx = 0;
    char **dest = malloc(sizeof(char *) * (nbmax + 1));
    dest[nbmax] = NULL;
    dest = my_alloc_array(str, limit, dest);
    for (int nbc = 0; nby < nbmax; nbc++, nbx++) {
        if (test_lim(str[nbc], limit)) {
            dest[nby][nbx] = '\0';
            nbx = 0, nby += 1, nbc++;
        }
        if (nby == nbmax) break;
        dest[nby][nbx] = str[nbc];
    }
    return dest;
}
