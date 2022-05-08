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
    LORDDITTOMUSIC,
    DUNGEON1MUSIC,
    DUNGEON2MUSIC,
    COUNTMUSICS
};

typedef struct s_music_t {
    sfMusic *musics_board[COUNTMUSICS];
}s_music;

s_music *init_musics(void);
void change_volume_sound_or_music(wininf *inf, int current);

#endif /* !MUSIC_H_ */
