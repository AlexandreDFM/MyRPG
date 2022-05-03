/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** camera_follow
*/

#include "rpg.h"

void update_camera(wininf *inf)
{
    if (!inf->camera.target) {
        return;
    }
    sfVector2f pos = sfSprite_getPosition(inf->camera.target);
    // sfVector2f size = sfView_getSize(inf->camera.view);
    // pos.x = my_clamp(pos.x, size.x / 2.0f, max_x - size.x / 2.0f);
    // pos.y = my_clamp(pos.y, size.y / 2.0f, max_y - size.y / 2.0f);
    if (inf->dungeon.in)
        pos = my_lerp(sfView_getCenter(inf->camera.view), pos, 6.0f * inf->time.dt);
    sfView_setCenter(inf->camera.view, pos);
    sfRectangleShape_setPosition(inf->transi, pos);
    sfRenderWindow_setView(inf->win, inf->camera.view);
}
