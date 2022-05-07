/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** entity
*/

#ifndef ENTITY_H_
    #define ENTITY_H_

    #include "rpg.h"

typedef enum anim_state_s {
    N_WALK,
    S_WALK,
    WE_WALK,
    D_WALK,
} anim_state_s;

typedef struct entity_t {
    sfSprite *sp;
    sfIntRect rect;
    int width;
    int max;
    int loop_type;
    int sign;
} entity;

#endif
