/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** log_system
*/

#include "rpg.h"

void update_logs(logline *log, wininf *inf, sfVector2f view, dline *line)
{
    apply_transparency(log);
    sfVector2f np = my_lerp(log->oldtarget,
        log->target, inf->time.dt * 3.0f);
    sfVector2f offseted = np;
    offseted.x += view.x; offseted.y += view.y;
    for (int i = 0; i < line->nblines; i++) {
        if (log->alive != -1) {
            sfSprite_setPosition(line->sps[i], offseted);
            sfRenderWindow_drawSprite(inf->win, line->sps[i], 0);
        }
    }
    if (log->time > 3.0f && log->alive == 1) {
        log->time = 0.0f;
        log->alive = 0;
    }
    log->oldtarget = np;
}

void draw_logs(wininf *inf)
{
    sfVector2f view = sfView_getCenter(inf->camera.view);
    if (!inf->logs) return;
    sfSprite_setPosition(inf->logs_textbox, view);
    sfColor col = sfSprite_getColor(inf->logs_textbox);
    if (((logline*)inf->logs->data)->alive != -1) {
        col.a = my_lerpf(col.a, 255.0f, inf->time.dt * 4.0f);
    } else {
        col.a = my_lerpf(col.a, 0.0f, inf->time.dt * 4.0f);
    }
    sfSprite_setColor(inf->logs_textbox, col);
    sfRenderWindow_drawSprite(inf->win, inf->logs_textbox, NULL);
    for (list *t = inf->logs; t; t = t->next) {
        logline *log = t->data;
        dline *line = log->line;
        update_logs(log, inf, view, line);
        log->time += inf->time.dt;
    }
}
