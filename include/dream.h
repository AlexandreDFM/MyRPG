/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** dream
*/

#include "rpg.h"
#include "cinematics_elements.h"

#ifndef DREAM_H_
#define DREAM_H_

enum dreamscene_t {
    DREAMINIT,
    DELETEDREAM
};

typedef struct dream_assets_t {
    enum dreamscene_t plan;
    int color;
    cine_ele b_dream[3];
    sfMusic *music;
} dream_a;

void delete_dream(wininf *inf);
dream_a *create_dream(wininf *inf);

#endif /* !DREAM_H_ */
