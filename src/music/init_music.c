/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_music
*/

#include "music.h"

void set_sound_musics(wininf *inf, int volume)
{
    for (int i = 0; i < COUNTMUSICS; i++)
        sfMusic_setVolume(inf->music->musics_board[i], volume);
}

s_music *init_musics()
{
    s_music *music = my_malloc(sizeof(s_music));
    char **csvmusics = load_csv("./csv/music.csv");
    for (int i = 1, j = 0; csvmusics[i] != NULL; i++, j++) {
        char **actualmusic = my_strtwa(csvmusics[i], ";\n");
        music->musics_board[j] = my_music_from_file(actualmusic[0]);
        sfMusic_setLoop(music->musics_board[j], sfTrue);
        my_free_array(actualmusic);
    }
    return music;
}
