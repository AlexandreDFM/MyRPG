/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** scene_handler
*/

#include "rpg.h"

void handle_scene(wininf *infos, player *p)
{
    sfRenderWindow_clear(infos->win, sfBlack);
    if (infos->c_scene == INTRO || infos->c_scene == QUIZ
    || infos->c_scene == DREAM || infos->c_scene == DITTO) {
        if (infos->c_scene == INTRO) draw_intro(infos);
        if (infos->c_scene == DREAM) draw_dream(infos);
        if (infos->c_scene == QUIZ) draw_quiz(infos, p);
        if (infos->c_scene == DITTO) draw_ditto(infos);
    } else if (infos->c_scene == MAIN_MENU) {
        draw_menu(infos, infos->main_menu);
        if (infos->c_menu == LOAD_SAVE) draw_menu(infos, infos->current_menu);
        if (infos->c_menu == OPTIONS){
            draw_menu(infos, infos->current_menu);
            if (((choices *)infos->current_menu->selected->data)->ptr < 3
                && infos->pressed == 0) {
                change_volume(infos);
            }
        }
        if (infos->c_menu == KEYBINDS_M)
            draw_menu(infos, infos->change_keys_menu);
    } else {
        if (infos->c_scene == HOME)
            draw_home(infos);
        int cs = infos->c_scene;
        if (cs == VILLAGE || cs == BEKIPAN || cs == DOJO || cs == DITTOLAND ||
            cs == INTERIOR)
            draw_static_scene(infos, infos->scenes[infos->c_scene]);
        else if (infos->c_scene == DUNGEON)
            draw_dungeon(infos, p);
        player_direction_management(infos, p);
        draw_player(infos, p);
        if (infos->transition) {
            update_transition(infos, *p);
            sfRenderWindow_drawRectangleShape(infos->win, infos->transi, 0);
        }
        if (infos->interacting && infos->ui.dialog) {
            sfRenderWindow_drawSprite(infos->win,
            infos->ui.background, 0);
            if (infos->ui.dialog) {
                dline *d = infos->ui.dialog->data;
                if (d && d->sps[d->cline]) {
                    for (int i = 0; i < d->nblines; i++) {
                        sfRenderWindow_drawSprite(infos->win,
                        d->sps[i], 0);
                    }
                    if (d->time > infos->ui.text_delay && d->i < d->max) {
                        sfIntRect nr = (sfIntRect){0, d->height * d->cline, d->steps[d->i],
                        d->height};
                        if (d->steps[d->i] > d->steps[d->i + 1]) {
                            d->cline++;
                            d->i++;
                        } else {
                            sfSprite_setTextureRect(d->sps[d->cline], nr);
                            d->i++;
                            d->time = 0.0f;
                        }
                    }
                    d->time += infos->time.dt;
                }
            }
        }
        if (infos->c_menu == PAUSE) {
            draw_menu(infos, infos->pause_menu);
            update_playtime(infos);
        }
        if (infos->c_menu != PAUSE && infos->c_menu != NONE) {
            center_menu(infos->current_menu, infos, p);
            draw_menu(infos, infos->current_menu);
            if (infos->c_menu == USE_ITEM) {
                center_menu(infos->inventory_menu, infos, p);
                draw_menu(infos, infos->inventory_menu);
            }
            if (infos->c_menu == IG_OPTIONS && infos->pressed == 0) {
                change_volume_ig(infos);
            }
        }
    }
    draw_logs(infos);
    update_time(infos);
    sfRenderWindow_display(infos->win);
}

scene create_home(wininf *infos, int id)
{
    my_printf(stdout, "Loading HOME Scene:\n");
    scene scene;
    scene.statics = 0; scene.animated = 0; scene.colls = 0; scene.pnjs = 0;
    sfImage *atlas = infos->atlases.atlas;
    char **arr = infos->atlases.houses;
    char **hinfo = my_strtwa(arr[id], ";\n");
    sfIntRect r = (sfIntRect){my_atoi(hinfo[1]), my_atoi(hinfo[2]),
        my_atoi(hinfo[3]), my_atoi(hinfo[4])};
    add_to_list(&scene.statics, atlas_to_sprite(r, atlas));
    sfSprite_setPosition(scene.statics->data, (sfVector2f){163.0f, 81.0f});
    my_free_array(hinfo);
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
    my_free_array(hinfo);
    return scene;
}

scene create_static_env(wininf *inf, int id)
{
    scene scene;
    my_printf(stdout, "Loading Scene %d:\n", id);
    scene.animated = 0, scene.colls = 0, scene.statics = 0, scene.pnjs = 0;
    char **arr = my_strtwa(inf->atlases.scenes[id], ";\n");
    for (int i = 0; arr[i]; i += 4) {
        sfIntRect r = (sfIntRect){my_atoi(arr[i]), my_atoi(arr[i + 1]),
            my_atoi(arr[i + 2]), my_atoi(arr[i + 3])};
        add_to_list(&scene.statics, atlas_to_sprite(r, inf->atlases.atlas));
    }
    place_decorations(inf->atlases.scenes[id + 1], inf->atlases.atlas,
        inf->atlases.statics, &scene.animated);
    id = id == 0 ? 22 : id > 6 ? id / 2 + 25 : 23 + id / 2 - 1;
    add_pnjs(inf->atlases, id, &scene);
    add_collisions(inf->atlases.collisions[id], &scene.colls);
    my_free_array(arr);
    return scene;
}
