/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** camera_follow
*/

#include "rpg.h"

sfIntRect get_bounding_box_scene(wininf *inf)
{
    int cs = inf->c_scene;
    sfIntRect r = (sfIntRect){0, 0, 1000.0f, 1000.0f};
    if (cs == DUNGEON) {
        r.width = 1230.0f; r.height = 1230.0f;
    } if (cs == VILLAGE) {
        r.width = 958; r.height = 719;
    } if (cs == HOME) {
        r.width = 550; r.height = 526;
    } if (cs == BEKIPAN) {
        r.width = 768; r.height = 420;
    } if (cs == DOJO) {
        r.width = 624; r.height = 384;
    } if (cs == DITTOLAND) {
        r.width = 454; r.height = 535;
    }
    return r;
}

void update_camera(wininf *inf, player *p)
{
    if (!inf->camera.target)
        return;
    sfVector2f pos = sfSprite_getPosition(inf->camera.target);
    sfVector2f center = sfView_getCenter(inf->camera.view);
    if (inf->dungeon.in) {
        pos = my_lerp(center, pos, 6.0f * inf->time.dt);
    }
    sfIntRect r = get_bounding_box_scene(inf);
    sfVector2f view_size = sfView_getSize(inf->camera.view);
    pos.x = pos.x - view_size.x / 2.0f < r.left ? view_size.x / 2.0f : pos.x;
    pos.x = pos.x + view_size.x / 2.0f > r.width ?
        r.width - view_size.x / 2.0f : pos.x;
    pos.y = pos.y - view_size.y / 2.0f < 0 ? view_size.y / 2.0f : pos.y;
    pos.y = pos.y + view_size.y / 2.0f > r.height ?
        r.height - view_size.y / 2.0f : pos.y;
    sfView_setCenter(inf->camera.view, pos);
    sfRectangleShape_setPosition(inf->transi, pos);
    sfRenderWindow_setView(inf->win, inf->camera.view);
}
