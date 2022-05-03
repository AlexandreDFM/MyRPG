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
    cditto->ditto[0] = c_eles("ditto.png", (sfVector2f){400 + 250, 0 + 250},
        (sfIntRect){0, 0, 220, 193});
    cditto->ditto[1] = c_eles("ditto.png",
    (sfVector2f){1920 + (rand() % 1000), 0}, (sfIntRect){0, 0, 220, 193});
    sfColor ditto1 = sfSprite_getColor(cditto->ditto[1].sprite);
    sfSprite_setColor(cditto->ditto[1].sprite,
        (sfColor){ditto1.r, ditto1.g, ditto1.b, ditto1.a - 125});
    cditto->ditto[2] = c_eles("ditto.png",
    (sfVector2f){-220 - (rand() % 1000), -300}, (sfIntRect){0, 0, 220, 193});
    sfColor ditto2 = sfSprite_getColor(cditto->ditto[2].sprite);
    sfSprite_setColor(cditto->ditto[2].sprite,
        (sfColor){ditto2.r, ditto2.g, ditto2.b, ditto2.a - 125});
    cditto->ditto[3] = c_eles("ditto.png",
    (sfVector2f){-220 - (rand() % 1000), 500}, (sfIntRect){0, 0, 220, 193});
    sfColor ditto3 = sfSprite_getColor(cditto->ditto[3].sprite);
    sfSprite_setColor(cditto->ditto[3].sprite,
        (sfColor){ditto3.r, ditto3.g, ditto3.b, ditto3.a - 125});
    cditto->conga = sfMusic_createFromFile("music/00_conga.ogg");
    sfMusic_setLoop(cditto->conga, sfTrue);
    cditto->color = my_hsvtorgb(rand() % 360, 29, 100); return cditto;
}
