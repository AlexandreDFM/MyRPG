/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** log_system
*/

#include "rpg.h"

char *print_log(wininf *inf, char *msg, va_list ap)
{
    my_fprintf_log(inf->log_file, msg, ap);
    fclose(inf->log_file);
    inf->log_file = fopen(inf->log_path, "r+");
    char * line = NULL;
    size_t len = 0;
    while (getline(&line, &len, inf->log_file) != -1);
    line[my_strlen(line) - 1] = '\0';
    return line;
}

void move_up(wininf *inf, int off)
{
    int index = 0;
    for (list *t = inf->logs; t; t = t->next, index++) {
        logline *log = t->data;
        log->target = (sfVector2f){log->target.x, log->target.y - off};
        int alived = log->alive;
        log->alive = log->alive != -1 ? index < 3 : log->alive;
        if (log->alive != alived) log->time = 0.0f;
    }
}

void add_log(wininf *inf, char *msg, ...)
{
    va_list ap; va_start(ap, msg);
    list *nl = malloc(sizeof(list));
    char *result = print_log(inf, msg, ap);
    dline *line = load_line(result, FONT_SIZE, inf, malloc);
    logline *nlog = malloc(sizeof(logline));
    nlog->line = line; nlog->alive = 1; nlog->time = 0.0f;
    sfVector2f view = sfView_getCenter(inf->camera.view);
    nlog->target = (sfVector2f){-80.0f, 60.0f};
    nlog->oldtarget = (sfVector2f){-80.0f, 60.0f};
    sfIntRect rect = (sfIntRect){0, 0, line->steps[line->max], line->height};
    for (int i = 0; i < line->nblines; i++) {
        sfVector2f ta = (sfVector2f){nlog->target.x + view.x,
            nlog->target.y + view.y};
        sfSprite_setColor(line->sps[i], sfColor_fromRGBA(255, 255, 255, 0));
        sfSprite_setPosition(line->sps[i], ta);
        sfSprite_setTextureRect(line->sps[i], rect);
    }
    nl->data = nlog; nl->next = inf->logs; inf->logs = nl;
    int off = line->height + 1;
    move_up(inf, off);
}

void apply_transparency(logline *ll)
{
    dline *dl = ll->line;
    sfColor col = sfSprite_getColor(dl->sps[0]);
    if (ll->alive == 1) {
        col.a = my_lerpf(col.a, 255.0f, ll->time / 4.0f);
    } else {
        col.a = my_lerpf(col.a, 0.0f, ll->time);
        if (col.a < 1) ll->alive = -1;
    }
    for (int i = 0; i < dl->nblines; i++) {
        sfSprite_setColor(dl->sps[i], col);
    }
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
        log->time += inf->time.dt;
        log->oldtarget = np;
    }
}
