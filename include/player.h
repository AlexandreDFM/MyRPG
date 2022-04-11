/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** player
*/

#ifndef PLAYER_H_
#define PLAYER_H_

    #include "rpg.h"

typedef struct stat_s {
    float speed;
} stat;

typedef struct player_s {
    struct stat_s *st;
    sfSprite *sp;
} player;

#endif /* !PLAYER_H_ */
