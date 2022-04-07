/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** scene_handler
*/

#include "rpg.h"
#include "scenes.h"

void handle_scene(wininf *infos, player p)
{
    sfRenderWindow_clear(infos->win, sfBlack);
    if (infos->c_scene == HOME)
        draw_home(infos);
    if (infos->c_scene)
        draw_static_scene(infos, infos->scenes[infos->c_scene]);
    draw_player(infos, p);
    if (infos->transition) {
        update_transition(infos, p);
        sfRenderWindow_drawRectangleShape(infos->win, infos->transition_rect, 0);
    }
    if (infos->interacting) {
        sfRenderWindow_drawSprite(infos->win,
        infos->ui.background, 0);
        dline *d = infos->ui.dialog;
        sfRenderWindow_drawSprite(infos->win, d->sp, 0);
        if (d->time > infos->ui.text_delay && d->steps[d->i + 1]) {
            sfIntRect new_rect = (sfIntRect){0, 0, d->steps[d->i], d->height};
            sfSprite_setTextureRect(d->sp, new_rect);
            d->i++;
            d->time = 0.0f;
        }
        d->time += infos->time.dt;
    }
    sfRenderWindow_display(infos->win);
    update_time(infos);
}

scene create_home(wininf *infos, int id)
{
    printf("Loading HOME Scene:\n");
    scene scene;
    scene.statics = 0; scene.animated = 0; scene.colls = 0; scene.pnjs = 0;
    sfImage *atlas = infos->atlases.atlas;
    char **arr = infos->atlases.houses;
    char **hinfo = my_strtwa(arr[id], ";\n");
    sfIntRect r = (sfIntRect){my_atoi(hinfo[1]), my_atoi(hinfo[2]),
        my_atoi(hinfo[3]), my_atoi(hinfo[4])};
    add_to_list(&scene.statics, atlas_to_sprite(r, atlas));
    sfSprite_setPosition(scene.statics->data, (sfVector2f){163.0f, 81.0f});
    //FREE hinfo
    hinfo = my_strtwa(arr[0], ";\n");
    r = (sfIntRect){my_atoi(hinfo[1]), my_atoi(hinfo[2]),
        my_atoi(hinfo[3]), my_atoi(hinfo[4])};
    add_to_list(&scene.statics, atlas_to_sprite(r, atlas));
    place_decorations(arr[32], infos->atlases.atlas,
        infos->atlases.statics, &scene.animated);
    add_collisions(infos->atlases.collisions[id - 1], &scene.colls);
    add_pnjs(infos->atlases, id - 1, &scene);
    if (id == 5 || id == 9 || id == 14 || id == 17)
        return scene;
    place_decorations(arr[id + 32], infos->atlases.atlas,
        infos->atlases.statics, &scene.animated);
    return scene;
}

scene create_static_environment(wininf *inf, int id)
{
    scene scene;
    printf("Loading Scene %d:\n", id);
    scene.animated = 0, scene.colls = 0, scene.statics = 0;
    char **arr = my_strtwa(inf->atlases.scenes[id], ";\n");
    for (int i = 0; arr[i]; i += 4) {
        sfIntRect r = (sfIntRect){my_atoi(arr[i]), my_atoi(arr[i + 1]),
            my_atoi(arr[i + 2]), my_atoi(arr[i + 3])};
        add_to_list(&scene.statics, atlas_to_sprite(r, inf->atlases.atlas));
    }
    place_decorations(inf->atlases.scenes[id + 1], inf->atlases.atlas,
        inf->atlases.statics, &scene.animated);
    int oldid = id;
    id = id == 0 ? 22 : id > 6 ? id / 2 + 25 : 23 + id / 2 - 1;
    add_collisions(inf->atlases.collisions[id], &scene.colls);
    return scene;
}
