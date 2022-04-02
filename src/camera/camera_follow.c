/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** camera_follow
*/

#include "rpg.h"

void update_camera(camera c, float dt, sfRenderWindow *win, sfRectangleShape *transi)
{
    if (!c.target) {
        return;
    }
    // float max_x = 550.0f;
    // float max_y = 526.0f;
    float max_x = 958.0f;
    float max_y = 719.0f;
    sfVector2f pos = sfSprite_getPosition(c.target);
    sfVector2f size = sfView_getSize(c.view);
    pos.x = my_clamp(pos.x, size.x / 2.0f, max_x - size.x / 2.0f);
    pos.y = my_clamp(pos.y, size.y / 2.0f, max_y - size.y / 2.0f);
    sfView_setCenter(c.view, pos);
    sfRectangleShape_setPosition(transi, pos);
    sfRenderWindow_setView(win, c.view);
}
