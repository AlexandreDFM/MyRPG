/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** init_atlases
*/

#include "infos.h"
#include "atlas.h"

void create_atlases(wininf *inf)
{
    inf->atlases.atlas = sfImage_createFromFile("atlas.png");
    inf->atlases.pokemons_anim = load_csv("csv/pokemon_anims.csv");
    inf->atlases.houses = load_csv("csv/House.csv");
    inf->atlases.scenes = load_csv("csv/scenes.csv");
    inf->atlases.statics = load_csv("csv/statics.csv");
    inf->atlases.collisions = load_csv("csv/collisions.csv");
    inf->atlases.pnjs = load_csv("csv/pnjs.csv");
    inf->atlases.icons = load_csv("csv/icons.csv");
}
