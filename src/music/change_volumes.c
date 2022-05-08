/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** change_volumes
*/

#include "rpg.h"
#include "music.h"
#include "sounds.h"
#include "intro.h"
#include "dream.h"
#include "ditto.h"

void change_volumes_music(wininf *inf, int volume)
{
    if (inf->intro != NULL) {
        sfMusic_setVolume(inf->intro->i_music1, volume);
        sfMusic_setVolume(inf->intro->i_music2, volume);
    }
    if (inf->dream != NULL)
        sfMusic_setVolume(inf->dream->music, volume);
    if (inf->ditto != NULL)
        sfMusic_setVolume(inf->ditto->conga, volume);
    for (int i = 0; i < COUNTMUSICS; i++)
        sfMusic_setVolume(inf->music->musics_board[i], volume);
}

void change_volumes_sounds(wininf *inf, int volume)
{
    for (int i = 0; i < COUNTSOUNDS; i++)
        sfSound_setVolume(inf->sounds->sounds_board[i], volume);
}

void change_volume_sound_or_music(wininf *inf, int current)
{
    if (current == 1) {
        change_volumes_music(inf, inf->volumes[current]);
    } else if (current == 0) {
        change_volumes_sounds(inf, inf->volumes[current]);
    }
}
