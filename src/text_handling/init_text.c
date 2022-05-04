/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_text
*/

#include "rpg.h"

sfText *init_text(char *str, sfFont *font, sfVector2f pos, int size)
{
    sfText *text = my_text();
    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, size);
    sfText_setPosition(text, pos);
    return text;
}
