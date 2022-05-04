/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_camera
*/

#include "rpg.h"

camera init_camera(wininf inf)
{
    camera ca;
    ca.static_p = (sfVector2f){250.0f, 250.0f};
    ca.target = 0;
    ca.speed = 4.0f;
    ca.view = my_view();
    sfView_setCenter(ca.view, (sfVector2f){0.0f, 0.0f});
    sfView_setSize(ca.view, (sfVector2f){inf.mode.width, inf.mode.height});
    sfView_zoom(ca.view, 1.0f / SIZE);
    return ca;
}
