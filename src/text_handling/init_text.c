/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_text
*/

#include "rpg.h"

sfText *init_text(char *str, sfFont *font, sfVector2f pos)
{
    sfText *text = sfText_create();
    sfText_setString(text, str);
    sfText_setFont(text, font);
    sfText_setCharacterSize(text, 50);
    sfText_setPosition(text, pos);
    return text;
}
