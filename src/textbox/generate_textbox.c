/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** generate_textbox
*/

#include "rpg.h"

sfSprite *generate_textbox(sfVector2i size, sfImage *atlas)
{
    sfColor trans = sfColor_fromRGBA(32, 72, 104, 221);
    sfImage *new = sfImage_createFromColor(size.x, size.y, trans);
    add_corner(new, atlas, (sfVector2i){0, 0}, (sfVector2i){1232, 812});
    add_corner(new, atlas,
        (sfVector2i){0, size.y - 6}, (sfVector2i){1232, 846});
    add_corner(new, atlas,
        (sfVector2i){size.x - 9, 0}, (sfVector2i){1447, 812});
    add_corner(new, atlas,
        (sfVector2i){size.x - 9, size.y - 6}, (sfVector2i){1447, 846});
    leftright_border(size, new);
    topbot_border(size, new); sfSprite *sp = sfSprite_create();
    sfSprite_setTexture(sp, sfTexture_createFromImage(new, 0), sfFalse);
    sfImage_destroy(new); return sp;
}

void topbot_border(sfVector2i size, sfImage *new)
{
    for (int x = 9; x < size.x - 9; x++)
        sfImage_setPixel(new, x, 0, sfColor_fromRGB(168, 192, 224));
    for (int x = 9; x < size.x - 9; x++)
        sfImage_setPixel(new, x, 1, sfColor_fromRGB(96, 128, 248));
    for (int x = 9; x < size.x - 9; x++)
        sfImage_setPixel(new, x, 2, sfColor_fromRGB(96, 128, 248));
    for (int x = 9; x < size.x - 9; x++)
        sfImage_setPixel(new, x, 3, sfColor_fromRGB(72, 32, 248));
    for (int x = 9; x < size.x - 9; x++)
        sfImage_setPixel(new, x, size.y - 4, sfColor_fromRGB(72, 32, 248));
    for (int x = 9; x < size.x - 9; x++)
        sfImage_setPixel(new, x, size.y - 3, sfColor_fromRGB(96, 128, 248));
    for (int x = 9; x < size.x - 9; x++)
        sfImage_setPixel(new, x, size.y - 2, sfColor_fromRGB(96, 128, 248));
    for (int x = 9; x < size.x - 9; x++)
        sfImage_setPixel(new, x, size.y - 1, sfColor_fromRGB(168, 192, 224));
}

void leftright_border(sfVector2i size, sfImage *new)
{
    for (int i = 6; i < size.y - 6; i++) {
        sfImage_setPixel(new, 0, i, sfColor_fromRGB(168, 192, 224));
    }
    for (int x = 1; x < 6; x++) {
        for (int i = 6; i < size.y - 6; i++) {
            sfImage_setPixel(new, x, i, sfColor_fromRGB(96, 128, 248));
        }
    }
    for (int i = 6; i < size.y - 6; i++) {
        sfImage_setPixel(new, 6, i, sfColor_fromRGB(72, 32, 248));
    }
    for (int i = 6; i < size.y - 6; i++) {
        sfImage_setPixel(new, size.x - 1, i, sfColor_fromRGB(168, 192, 224));
    }
    for (int x = size.x - 2; x > size.x - 7; x--) {
        for (int i = 6; i < size.y - 6; i++) {
            sfImage_setPixel(new, x, i, sfColor_fromRGB(96, 128, 248));
        }
    }
    for (int i = 6; i < size.y - 6; i++) {
        sfImage_setPixel(new, size.x - 7, i, sfColor_fromRGB(72, 32, 248));
    }
}

void add_corner(sfImage *img, sfImage *atlas, sfVector2i pos, sfVector2i glo)
{
    for (int y = 0; y < 6; y++) {
        for (int x = 0; x < 9; x++) {
            sfColor col = sfImage_getPixel(atlas, glo.x + x, glo.y + y);
            sfImage_setPixel(img, pos.x + x, pos.y + y, col);
        }
    }
}
