/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** ditto
*/

#include "ditto.h"
#include "intro.h"

int my_cmp_values(sfVector2f size, float a, float b)
{
    if (a == size.x && b == size.y) {
        return 1;
    } else if (a <= size.x && b <= size.y) {
        return 2;
    } else {
        return 0;
    }
}

void ditto_clock(wininf *inf, ditto_a *cditto)
{
    if (inf->time.ditto_anim < 0.1f) return;
    cditto->ditto[1].pos.x -= 56; cditto->ditto[2].pos.x += 56;
    cditto->ditto[3].pos.x += 56;
    if (cditto->ditto[1].pos.x <= -426)
        cditto->ditto[1].pos.x = 1920 + rand() % 600;
    if (cditto->ditto[2].pos.x >= 1920 + 426)
        cditto->ditto[2].pos.x = -213 - rand() % 600;
    if (cditto->ditto[3].pos.x >= 1920 + 426)
        cditto->ditto[3].pos.x = -213 - rand() % 600;
    if (cditto->ditto[0].rect.left >= 213 * 3) {
        cditto->ditto[0].rect.left = 0; cditto->ditto[1].rect.left = 0;
        cditto->ditto[2].rect.left = 0; cditto->ditto[3].rect.left = 0;
    } else {
        cditto->ditto[0].rect.left += 213; cditto->ditto[1].rect.left += 213;
        cditto->ditto[2].rect.left += 213; cditto->ditto[3].rect.left += 213;
    }
    inf->time.ditto_anim = 0.0f;
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
    for (int i = 0; i < 4; i++) display_ele(inf->win, cditto->ditto[i]);
}

void draw_ditto(wininf *inf)
{
    if (inf->ditto == NULL) {
        inf->ditto = create_ditto(inf);
    }
    if (inf->ditto->plan != DELETEDITTO) {
        if (sfMusic_getStatus(inf->ditto->conga) != sfPlaying) {
            sfMusic_play(inf->ditto->conga);
        }
        ditto_clock(inf, inf->ditto);
        ditto(inf, inf->ditto);
    }
    if (inf->ditto->plan == DELETEDITTO) delete_ditto(inf);
}
