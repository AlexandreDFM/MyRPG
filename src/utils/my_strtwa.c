/*
** EPITECH PROJECT, 2022
** my_strtwa
** File description:
** Function to reproduce strtok but output is double array
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
    for (int nbc = 0; str[nbc] != '\0'; nbc++, nbx++) {
        if (test_lim(str[nbc], limit)) {
            dest[nby] = malloc(sizeof(char) * (nbx + 1));
            dest[nby][nbx] = '\0';
            nby += 1, nbx = 0;
        }
    }
    dest[nby] = malloc(sizeof(char) * (nbx + 1));
    dest[nby][nbx] = '\0';
    return dest;
}

char **my_strtwa(char const *str, char *limit)
{
    int nbmax = (nb_not_valid(str, limit) + 1), nby = 0, nbx = 0;
    char **dest = malloc(sizeof(char *) * (nbmax + 1));
    dest[nbmax] = NULL;
    dest = my_alloc_array(str, limit, dest);
    for (int nbc = 0; nby < nbmax - 1; nbc++, nbx++) {
        if (test_lim(str[nbc], limit)) {
            dest[nby][nbx] = '\0';
            nbx = 0, nby += 1, nbc++;
        }
        dest[nby][nbx] = str[nbc];
    }
    dest[nby] = 0;
    return dest;
}
