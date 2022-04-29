/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** ditto
*/

#include "ditto.h"
#include "intro.h"

void ditto_clock(wininf *inf, ditto_a *cditto)
{
    if (inf->time.ditto_anim > 0.1f) {
        cditto->ditto[1].pos.x -= 56; cditto->ditto[2].pos.x += 56;
        cditto->ditto[3].pos.x += 56;
        if (cditto->ditto[1].pos.x <= 0 - 220)
            cditto->ditto[1].pos.x = 1920 + rand() % 300;
        if (cditto->ditto[2].pos.x >= 1920 + 220)
            cditto->ditto[2].pos.x = -220 - rand() % 300;
        if (cditto->ditto[3].pos.x >= 1920 + 220)
            cditto->ditto[3].pos.x = -220 - rand() % 300;
        if (cditto->ditto[0].rect.left >= 220 * 3) {
            cditto->ditto[0].rect.left = 0; cditto->ditto[1].rect.left = 0;
            cditto->ditto[2].rect.left = 0; cditto->ditto[3].rect.left = 0;
        } else {
            cditto->ditto[0].rect.left += 220;
            cditto->ditto[1].rect.left += 220;
            cditto->ditto[2].rect.left += 220;
            cditto->ditto[3].rect.left += 220;
        }
        inf->time.ditto_anim = 0.0f;
    }
}

void background_clock(wininf *inf, ditto_a *cditto)
{
    if (inf->time.ditto_anim2 > 1.0f) {
        cditto->color = my_hsvtorgb(rand() % 360, 29, 100);
        inf->time.ditto_anim2 = 0.0f;
    }
}

void ditto(wininf *inf, ditto_a *cditto)
{
    ditto_clock(inf, cditto);
    background_clock(inf, cditto);
    if (sfMusic_getStatus(cditto->conga) == 0) sfMusic_play(cditto->conga);
    sfRenderWindow_clear(inf->win, cditto->color);
    for (int i = 0; i < 4; i++) display_eles(inf->win, cditto->ditto[i]);
}

void draw_ditto(wininf *inf)
{
    if (inf->ditto == NULL) {
        inf->ditto = create_ditto(inf);
    }
    if (inf->ditto->plan != DELETEDITTO) {
        if (sfMusic_getStatus(inf->ditto->conga) == 0) {
            sfMusic_play(inf->ditto->conga);
        }
        ditto_clock(inf, inf->ditto);
        ditto(inf, inf->ditto);
    }
    if (inf->ditto->plan == DELETEDITTO) delete_ditto(inf);
}
