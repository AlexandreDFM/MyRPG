/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** ditto
*/

#include "rpg.h"
#include "cinematics_elements.h"

#ifndef DITTO_H_
    #define DITTO_H_

enum dittoscene_t {
    DITTOINIT,
    DELETEDITTO
};

typedef struct ditto_assets_t {
    enum dittoscene_t plan;
    cine_ele ditto[4];
    sfColor color;
    sfMusic *conga;
} ditto_a;

void delete_ditto(wininf *inf);
ditto_a *create_ditto(wininf *inf);
sfColor my_hsvtorgb(float H, float S, float V);
cine_ele c_eles(char *tpath, sfVector2f pos, sfIntRect rect);

#endif /* !DITTO_H_ */
