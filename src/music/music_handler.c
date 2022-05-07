/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** music_handler
*/

#include "music.h"

void handle_one_music(wininf *inf, int scene, int tabmusic)
{
    if (inf->c_scene == scene &&
    sfMusic_getStatus(inf->music->musics_board[tabmusic]) != sfPlaying) {
        sfMusic_play(inf->music->musics_board[tabmusic]);
    } else if (inf->c_scene != scene &&
    sfMusic_getStatus(inf->music->musics_board[tabmusic]) == sfPlaying) {
        sfMusic_stop(inf->music->musics_board[tabmusic]);
    }
}

void handle_multiple_music(wininf *inf, sfIntRect s, int tabmusic)
{
    if ((inf->c_scene == s.height || inf->c_scene == s.left ||
    inf->c_scene == s.top || inf->c_scene == s.width) &&
    sfMusic_getStatus(inf->music->musics_board[tabmusic]) != sfPlaying) {
        sfMusic_play(inf->music->musics_board[tabmusic]);
    } else if (inf->c_scene != s.height && inf->c_scene != s.left &&
    inf->c_scene != s.top && inf->c_scene != s.width &&
    sfMusic_getStatus(inf->music->musics_board[tabmusic]) == sfPlaying) {
        sfMusic_stop(inf->music->musics_board[tabmusic]);
    }
}

void handle_music(wininf *inf)
{
    handle_multiple_music(inf, (sfIntRect)
    {HOME, INTERIOR, -1, -1}, HOMEMUSIC);
    handle_one_music(inf, MAIN_MENU, MENUMUSIC);
    handle_one_music(inf, DITTOLAND, DITTOLANDMUSIC);
    handle_one_music(inf, DUNGEON, DUNGEON1MUSIC);
    handle_multiple_music(inf, (sfIntRect)
    {VILLAGE, BEKIPAN, DOJO, -1}, VILLAGEMUSIC);
}
