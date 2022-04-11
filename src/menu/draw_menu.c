/*
** EPITECH PROJECT, 2022
** Visual Studio Live Share (Workspace)
** File description:
** draw_menu
*/

#include "rpg.h"

void draw_menu(wininf *inf)
{
    char *str = "Press to start";
    sfVector2f pos = {500, 500};
    sfText *text = sfText_create();
    sfText_setFont(text, inf->ui.font);
    sfText_setString(text, str);
    sfText_setCharacterSize(text, 50);
    sfText_setPosition(text, pos);
    sfRenderWindow_drawText(inf->win, text, NULL);
}
