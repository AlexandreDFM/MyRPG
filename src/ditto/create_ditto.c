/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** c_eles
*/

#include "intro.h"
#include "ditto.h"

cine_ele c_eles(char *tpath, sfVector2f pos, sfIntRect rect)
{
    cine_ele ele;
    ele.sprite = sfSprite_create();
    sfTexture *texture = sfTexture_createFromFile(tpath, NULL);
    ele.pos = pos;
    ele.rect = rect;
    ele.resize = (sfVector2f) {3, 3};
    sfSprite_setTexture(ele.sprite, texture, sfTrue);
    sfSprite_setPosition(ele.sprite, ele.pos);
    sfSprite_setScale(ele.sprite, ele.resize);
    sfSprite_setTextureRect(ele.sprite, ele.rect);
    return ele;
}

void display_eles(sfRenderWindow *window, cine_ele ele)
{
    sfSprite_setPosition(ele.sprite, ele.pos);
    sfSprite_setTextureRect(ele.sprite, ele.rect);
    sfSprite_setScale(ele.sprite, ele.resize);
    sfRenderWindow_drawSprite(window, ele.sprite, NULL);
}

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
    cditto->color = my_hsvtorgb(rand() % 360, 29, 100);
    return cditto;
}
