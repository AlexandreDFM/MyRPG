/*
** EPITECH PROJECT, 2022
** B-CPE-200-NCE-2-1-lemin-antoine.frankel
** File description:
** checks
*/

#include "rpg.h"

int check_char(char c, char *presence)
{
    for (int i = 0; presence[i] != '\0'; i++) {
        if (c == presence[i]) {
            return 1;
        }
    }
    return 0;
}

int pos_char(char *string, char *presence)
{
    if (string == NULL) return -1;
    for (int i = 0; string[i] != '\0'; i++) {
        if (check_char(string[i], presence) == 1) return i;
    }
    return -1;
}

int check_string(char *string, char *presence)
{
    if (string == NULL) return 1;
    for (int i = 0; string[i] != '\0'; i++) {
        if (check_char(string[i], presence) == 1) return 1;
    }
    return 0;
}

int count_char(char *string, char c)
{
    if (string == NULL) return 0;
    int nb_char = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == c) nb_char += 1;
    }
    return nb_char;
}
