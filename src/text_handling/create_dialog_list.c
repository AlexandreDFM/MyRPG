/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_dialog_list
*/

#include "rpg.h"

list *create_dialog_list(wininf *inf, char *path, sfVector2f poubelle)
{
    list *l = 0;
    char **arr = load_csv(path);
    dline *line;
    poubelle.x -= sfSprite_getTextureRect(inf->ui.background).width / 2 - 10;
    poubelle.y -= sfSprite_getTextureRect(inf->ui.background).height / 2 - 5;
    for (int i = 0; arr[i]; i++) {
        line = load_line(arr[i], FONT_SIZE, inf, my_malloc);
        sfSprite_setPosition(line->sp, poubelle);
        push_back(&l, line);
    }
    return l;
}
