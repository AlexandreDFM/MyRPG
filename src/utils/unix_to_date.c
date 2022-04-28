/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** unix_to_date
*/

#include "rpg.h"

char *unix_to_date(long int seconds)
{
    date_t t;
    char *ans = malloc(sizeof(char) * 100);
    int daysofmonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    long int curryear = 1970, extradays, index = 0, date, month = 0;
    long int hours, minutes, secondss, flag = 0;
    long int daystillnow = seconds / (24 * 60 * 60);
    long int extratime = seconds % (24 * 60 * 60);
    while (daystillnow >= 365) {
        if (curryear % 400 == 0 || (curryear % 4 == 0 && curryear % 100 != 0))
            daystillnow -= 366;
        else daystillnow -= 365;
        curryear += 1;
    } extradays = daystillnow + 1;
    if (curryear % 400 == 0 || (curryear % 4 == 0 && curryear % 100 != 0))
        flag = 1;
    if (flag == 1) {
        while (1) {
            if (index == 1) {
                if (extradays - 29 < 0) break;
                month += 1; extradays -= 29;
            } else {
                if (extradays - daysofmonth[index] < 0) break;
                month += 1; extradays -= daysofmonth[index];
            } index += 1;
        }
    }
    else {
        while (1) {
            if (extradays - daysofmonth[index] < 0) break;
            month += 1; extradays -= daysofmonth[index]; index += 1;
        }
    }
    if (extradays > 0) {
        month += 1;
        date = extradays;
    }
    else {
        if (month == 2 && flag == 1) date = 29;
        else date = daysofmonth[month - 1];
    }
    hours = extratime / 3600 + 2;
    minutes = (extratime % 3600) / 60;
    secondss = (extratime % 3600) % 60;

    strcat(ans, my_itoa(date));
    strcat(ans, "/");
    strcat(ans, my_itoa(month));
    strcat(ans, "/");
    strcat(ans, my_itoa(curryear));
    strcat(ans, " ");
    strcat(ans, my_itoa(hours));
    strcat(ans, ":");
    strcat(ans, my_itoa(minutes));
    strcat(ans, ":");
    strcat(ans, my_itoa(secondss));
    return ans;
}
