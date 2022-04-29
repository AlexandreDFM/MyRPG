/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** free_musics
*/

#include "rpg.h"
#include "intro.h"
#include "ditto.h"
#include "cinematics_elements.h"


void free_musics(wininf *inf)
{
    if (inf->intro != NULL) {
        sfMusic_stop(inf->intro->i_music1);
        sfMusic_stop(inf->intro->i_music2);
        sfMusic_destroy(inf->intro->i_music1);
        sfMusic_destroy(inf->intro->i_music2);
        //delete_intro(inf);
    }
}
