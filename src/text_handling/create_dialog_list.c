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
    float starting = poubelle.y;
    for (int i = 0; arr[i]; i++) {
        line = load_line(arr[i], FONT_SIZE, inf, my_malloc);
        for (int y = 0; y < line->nblines; y++) {
            sfSprite_setPosition(line->sps[y], poubelle);
            poubelle.y += line->height;
        }
        poubelle.y = starting;
        push_back(&l, line);
    }
    return l;
}
