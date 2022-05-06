/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** c_eles
*/

#include "intro.h"
#include "ditto.h"

ditto_a *create_ditto(wininf *inf)
{
    ditto_a *cditto = malloc(sizeof(ditto_a)); cditto->plan = DITTOINIT;
    for (int i = 0, j = 1; i < 4; i++, j++)
        cditto->ditto[i] = c_ele(inf->atlases.atlas, "./csv/ditto.csv", j);
    for (int i = 1; i < 4; i++) {
        sfColor ditto = sfSprite_getColor(cditto->ditto[i].sprite);
        sfSprite_setColor(cditto->ditto[i].sprite,
        sfColor_fromRGBA(ditto.r, ditto.g, ditto.b, ditto.a - 125));
    }
    cditto->conga = my_music_from_file("music/00_conga.ogg");
    sfMusic_setLoop(cditto->conga, sfTrue);
    cditto->color = my_hsvtorgb(rand() % 360, 29, 100); return cditto;
}
