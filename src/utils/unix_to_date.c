/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** unix_to_t.date
*/

#include "rpg.h"

void get_dateinfo(long int ti, date_t *t)
{
    int *arr = malloc(sizeof(int) * 12);
    int arri[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    for (int i = 0; i < 12; i++) arr[i] = arri[i];
    t->daysofmonth = arr;
    t->curryear = 1970;
    t->extradays = 0;
    t->index = 0;
    t->date = 0;
    t->month = 0;
    t->hours, t->minutes, t->secondss, t->flag = 0;
    t->daystillnow = ti / (24 * 60 * 60);
    t->extratime = ti % (24 * 60 * 60);
}

void fill_timeinf(char **ans, date_t t)
{
    get_int_len(t.date) != 2 ? my_strcat(*ans, "0") : 0;
    my_strcat(*ans, my_itoa(t.date));
    my_strcat(*ans, "/");
    get_int_len(t.month) < 2 ? my_strcat(*ans, "0") : 0;
    my_strcat(*ans, my_itoa(t.month));
    my_strcat(*ans, "/");
    my_strcat(*ans, my_itoa(t.curryear));
    my_strcat(*ans, " ");
    get_int_len(t.hours) != 2 ? my_strcat(*ans, "0") : 0;
    my_strcat(*ans, my_itoa(t.hours));
    my_strcat(*ans, ":");
    get_int_len(t.minutes) != 2 ? my_strcat(*ans, "0") : 0;
    my_strcat(*ans, my_itoa(t.minutes));
    my_strcat(*ans, ":");
    get_int_len((int)t.secondss) != 2 ? my_strcat(*ans, "0") : 0;
    my_strcat(*ans, my_itoa(t.secondss));
}

void is_bisextile(date_t *t)
{
    while (t->extradays - 29 < 0) {
        if (t->index == 1) {
            t->month += 1; t->extradays -= 29; t->index += 1;
            continue;
        }
        if (t->extradays - t->daysofmonth[t->index] < 0) break;
        t->month += 1; t->extradays -= t->daysofmonth[t->index];
        t->index += 1;
    }
}

void handle_bisextile(date_t *t)
{
    if (t->flag == 1) {
        is_bisextile(t);
        return;
    }
    while (1) {
        if (t->extradays - t->daysofmonth[t->index] < 0) break;
        t->month += 1; t->extradays -= t->daysofmonth[t->index];
        t->index += 1;
    }
    if (t->extradays > 0) {
        t->month += 1;
        t->date = t->extradays;
    } else {
        if (t->month == 2 && t->flag == 1) t->date = 29;
        else t->date = t->daysofmonth[t->month - 1];
    }
}

char *unix_to_date(long int ti)
{
    ti += 7200;
    date_t t; get_dateinfo(ti, &t);
    char *ans = malloc(sizeof(char) * 11); my_memset(ans, '\0', 11);
    while (t.daystillnow >= 365) {
        if (t.curryear % 400 == 0 || (t.curryear % 4 == 0 && t.curryear % 100 != 0))
            t.daystillnow -= 366;
        else t.daystillnow -= 365;
        t.curryear += 1;
    } t.extradays = t.daystillnow + 1;
    if (t.curryear % 400 == 0 || (t.curryear % 4 == 0 && t.curryear % 100 != 0))
        t.flag = 1;
    handle_bisextile(&t);
    t.hours = t.extratime / 3600;
    t.minutes = (t.extratime % 3600) / 60;
    t.secondss = (t.extratime % 3600) % 60;
    fill_timeinf(&ans, t);
    return ans;
}
