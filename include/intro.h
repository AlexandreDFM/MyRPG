/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** intro
*/

#include "rpg.h"
#include "cinematics_elements.h"

#ifndef INTRO_H_
#define INTRO_H_

enum pkmintro_t {
    RDMPKM = 0,
    BEKIPAN1 = 1,
    BEKIPAN2 = 2,
    BEKIPAN1OMBRE = 3,
    BEKIPAN2OMBRE = 4,
};

enum introscene_t {
    PLAN0,
    PLAN1,
    PLAN2,
    PLAN3,
    PLAN4,
    PLAN5,
    PLAN6,
    DELETEINTRO,
};

typedef struct intro_assets_t {
    int valid;
    enum introscene_t plan;
    cine_ele pkmintro[4];
    cine_ele b_intro[5];
    sfEvent event;
    sfColor color;
    sfMusic *i_music1;
    sfMusic *i_music2;
} intro_a;

void move_sun(intro_a *rpg);
void manage_intro(wininf *inf);
intro_a *create_intro(wininf *inf);
void move_sun_reverse(intro_a *rpg);
void display_eles(sfRenderWindow *window, cine_ele ele);
void plan_clock(sfRenderWindow *window, wininf *inf, intro_a *rpg);
void move_rectintrotop(sfIntRect *rect, int modify, int max_value);
void move_rectintroleft(sfIntRect *rect, int modify, int max_value);
void move_rectintroleft2(sfIntRect *rect, int modify, int max_value);
void move_rectintroleft3(sfIntRect *rect, int modify, int max_value);

#endif
