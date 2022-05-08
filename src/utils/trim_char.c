/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** trim_char
*/

#include "rpg.h"

char *trim(char *s, char c)
{
    int writer = 0, reader = 0;
    while (s[reader]) {
        if (s[reader] != c) {
            s[writer++] = s[reader];
        }
        reader++;
    }
    s[writer] = 0;
    return s;
}
