/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** log_system
*/

#include "rpg.h"

void add_log(wininf *inf, char *msg)
{
    list *nl = malloc(sizeof(list));
    dline *line = load_line(msg, FONT_SIZE, inf, malloc);
    logline *nlog = malloc(sizeof(logline));
    nlog->line = line;
    nlog->target = (sfVector2f){0, 1070.0f};
    for (int i = 0; i < line->sps[i]; i++) {
        sfSprite_setPosition(line->sps[i], nlog->target);
    }
    nl->data = nlog;
    nl->next = inf->logs;
    inf->logs = nl;
    int off = 10 + line->height;
    for (list *t = inf->logs; t; t = t->next) {
        logline *log = t->data;
        log->target = (sfVector2f){log->target.x, log->target.y - off};
    }
}

void draw_logs(wininf *inf)
{
    for (list *t = inf->logs; t; t = t->next) {
        logline *log = t->data;
        dline *line = log->line;
        for (int i = 0; line->sps[i]; i++) {
            sfVector2f np = my_lerp(sfSprite_getPosition(line->sps[i]),
                log->target, inf->time.dt * 3.0f);
            sfSprite_setPosition(line->sps[i], np);
            sfRenderWindow_drawSprite(inf->win, line->sps[i], 0);
        }
    }
}
