/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** intro
*/

#include "rpg.h"
#include "intro.h"

void intro(sfRenderWindow *w, intro_a *rpg)
{
    if (rpg->plan == PLAN0) {
        display_ele(w, rpg->b_intro[0]);
        for (int i = 0; i < 3; i++) display_ele(w, rpg->pkmintro[i]);
    }
    if (rpg->plan == PLAN1) {
        display_ele(w, rpg->b_intro[0]);
        for (int i = 0; i < 3; i++) display_ele(w, rpg->pkmintro[i]);
    }
    if (rpg->plan == PLAN2) {
        display_ele(w, rpg->b_intro[1]);
        display_ele(w, rpg->b_intro[2]);
        display_ele(w, rpg->b_intro[0]);
        display_ele(w, rpg->pkmintro[1]);
    }
    if (rpg->plan == PLAN3) {
        display_ele(w, rpg->b_intro[0]);
        display_ele(w, rpg->pkmintro[BEKIPAN1]);
    }
    if (rpg->plan == PLAN4) {
        display_ele(w, rpg->b_intro[0]);
        display_ele(w, rpg->b_intro[3]);
    }
    if (rpg->plan == PLAN5) display_ele(w, rpg->b_intro[3]);
    if (rpg->plan == PLAN6) {
        display_ele(w, rpg->b_intro[0]);
        for (int i = 3; i > 0; i--) display_ele(w, rpg->b_intro[i]);
    }
    // if (rpg->plan == DITTO) {
    //     if (sfMusic_getStatus(rpg->conga) == 0) sfMusic_play(rpg->conga);
    //     sfRenderWindow_clear(w, rpg->color);
    //     for (int i = 0; i < 4; i++) display_ele(w, rpg->ditto[i]);
    // }
}

void draw_intro(wininf *inf)
{
    if (inf->intro == NULL) inf->intro = create_intro(inf);
    if (inf->intro->plan != DELETEINTRO) {
        if (sfMusic_getStatus(inf->intro->i_music1) == 0)
            sfMusic_play(inf->intro->i_music1);
        if (sfMusic_getStatus(inf->intro->i_music1) == 1
        && sfMusic_getStatus(inf->intro->i_music2) == 0) {
            sfMusic_play(inf->intro->i_music2);
        }
        plan_clock(inf->win, inf, inf->intro);
        intro(inf->win, inf->intro);
    }
    if (inf->intro->plan == DELETEINTRO) {
        sfMusic_stop(inf->intro->i_music1);
        sfMusic_stop(inf->intro->i_music2);
        sfMusic_destroy(inf->intro->i_music1);
        sfMusic_destroy(inf->intro->i_music2);
        //delete_intro(inf);
        inf->c_scene = MAIN_MENU;
    }
}
