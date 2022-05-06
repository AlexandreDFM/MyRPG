/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_sounds
*/

#include "sounds.h"

s_sounds *init_sounds()
{
    s_sounds *sounds = my_malloc(sizeof(s_sounds));
    char **csvsounds = load_csv("./csv/sounds.csv");
    for (int i = 1, j = 0; csvsounds[i] != NULL; i++, j++) {
        char **actualsound = my_strtwa(csvsounds[i], ";\n");
        sounds->sound_buffer[j] = my_buffer_from_file(actualsound[0]);
        sounds->sounds_board[j] = my_sound();
        sfSound_setBuffer(sounds->sounds_board[j], sounds->sound_buffer[j]);
        my_free_array(actualsound);
    }
    return sounds;
}
