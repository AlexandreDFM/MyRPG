/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** music
*/

#include "rpg.h"

#ifndef MUSIC_H_
#define MUSIC_H_

enum musicsidx {
    HOMEMUSIC,
    VILLAGEMUSIC,
    MENUMUSIC,
    DITTOLANDMUSIC,
    COUNTMUSICS
};

typedef struct s_music_t {
    sfMusic *musics_board[COUNT];
}s_music;

s_music *init_musics();

#endif /* !MUSIC_H_ */
