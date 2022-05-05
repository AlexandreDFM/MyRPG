/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** log_system
*/

#include "rpg.h"

char *print_log(wininf *inf, char *msg, va_list ap)
{
    my_fprintf_log(stdout, "Hello world %s %d\n", ap);
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    int count = 0;
    read = getline(&line, &len, inf->log_file);
    return line;
}

void add_log(wininf *inf, char *msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    list *nl = malloc(sizeof(list));
    char *result = print_log(inf, msg, ap);
    dline *line = load_line(result, FONT_SIZE, inf, malloc);
    free(result);
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
