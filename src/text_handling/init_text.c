/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_text
*/

#include "rpg.h"

sfText *init_text(char *str, sfFont *font)
{
    sfText *text = sfText_create();
    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, FONT_SIZE);
    return text;
}
