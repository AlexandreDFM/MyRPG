/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** call_quest
*/

#include "rpg.h"

void update_rects_dialog_quest(wininf *win)
{
    dline *c_line = (dline*)win->ui.dialog->data;
    if (c_line->i == c_line->max) {
        win->ui.dialog = win->ui.dialog->next;
        win->interacting = !win->ui.dialog ? 0 : win->interacting;
        win->quest = 1;
    } else {
        c_line->i = c_line->max - 1; c_line->cline = c_line->nblines - 1;
        for (int i = 0; i < c_line->nblines; i++) {
            sfSprite *sp = c_line->sps[i];
            sfTexture *t = (sfTexture *)sfSprite_getTexture(sp);
            sfVector2u si = sfTexture_getSize(t);
            sfSprite_setTextureRect(sp, (sfIntRect){0, c_line->height * i,
            si.x, c_line->height});
        }
    }
}

void int_manage_quest(wininf *win, pnj *closest,sfVector2f poubelle)
{
    if (!win->ui.dialog && win->quest == 0) {
        win->ui.dialog = create_dialog_list(win, closest->dialog, poubelle);
        win->quest = 2;
    } else if (win->ui.dialog && win->quest == 2) {
        update_rects_dialog_quest(win);
    } else {
        win->interacting = 0;
    }
}

void interact_pnj_quest(wininf *win, player *p)
{
    if (win->quest == 1 || win->quest == 3) {
        win->interacting = 0; return;
    }
    float min = 200.f; pnj *closest = 0;
    list *l = win->scenes[win->c_scene].pnjs;
    for (list *t = l; t; t = t->next) {
        pnj *cp = t->data;
        float cmn = manhattan_distance(sfSprite_getPosition(p->test), cp->pos);
        if (cmn < min) {
            min = cmn; closest = cp;
        }
    }
    sfVector2f poubelle = sfView_getCenter(win->camera.view);
    poubelle.y += 45.0f; win->interacting = 1;
    sfSprite_setPosition(win->ui.background, poubelle);
    int_manage_quest(win, closest, poubelle);
}
