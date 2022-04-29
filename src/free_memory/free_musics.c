/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** free_musics
*/

#include "rpg.h"
#include "intro.h"
#include "ditto.h"
#include "dream.h"
#include "cinematics_elements.h"

void free_musics(wininf *inf)
{
    if (inf->intro != NULL) delete_intro(inf);
    if (inf->ditto != NULL) delete_ditto(inf);
    if (inf->dream != NULL) delete_dream(inf);
}
