/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** camera_follow
*/

#include "rpg.h"

void update_camera(wininf *inf)
{
    if (!inf->camera.target)
        return;
    sfVector2f pos = sfSprite_getPosition(inf->camera.target);
    sfVector2f center = sfView_getCenter(inf->camera.view);
    if (inf->dungeon.in)
        pos = my_lerp(center, pos, 6.0f * inf->time.dt);
    sfView_setCenter(inf->camera.view, pos);
    sfRectangleShape_setPosition(inf->transi, pos);
    sfRenderWindow_setView(inf->win, inf->camera.view);
}
