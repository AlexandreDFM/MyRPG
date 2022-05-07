/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** sounds
*/

#include "rpg.h"

#ifndef SOUNDS_H_
#define SOUNDS_H_

enum soundsidx {
    ATTACK_BASIC,
    MENU_CANCEL,
    MENU_MOVE,
    MENU_OPEN,
    MENU_SELECT,
    BIG_REWARD,
    LEVEL_UP,
    RANK_UP,
    REWARD,
    COUNTSOUNDS
};

typedef struct s_sounds_t {
    sfSoundBuffer *sound_buffer[COUNTSOUNDS];
    sfSound *sounds_board[COUNTSOUNDS];
}s_sounds;

s_sounds *init_sounds();

#endif /* !SOUNDS_H_ */
