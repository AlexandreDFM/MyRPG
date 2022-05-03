/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** elements
*/

#include "rpg.h"

#ifndef ELEMENTS_H_
#define ELEMENTS_H_

typedef struct cine_ele_t {
    sfSprite *sprite;
    sfVector2f pos;
    sfIntRect rect;
    sfIntRect rimage;
    sfVector2f resize;
} cine_ele;

cine_ele c_ele(sfImage *img, char *csv, int idx);
void display_ele(sfRenderWindow *window, cine_ele ele);
void display_eles(sfRenderWindow *window, cine_ele ele);
cine_ele c_eles(char *tpath, sfVector2f pos, sfIntRect rect);

#endif /* !ELEMENTS_H_ */
