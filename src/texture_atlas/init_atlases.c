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
    inf->atlases.pokemons_rect = load_csv("csv/pokemon_rect.csv");
    inf->atlases.houses = load_csv("csv/house.csv");
    inf->atlases.scenes = load_csv("csv/scenes.csv");
    inf->atlases.statics = load_csv("csv/statics.csv");
    inf->atlases.collisions = load_csv("csv/collisions.csv");
    inf->atlases.pnjs =
    inf->lang ? load_csv("csv/pnjs_fr.csv") : load_csv("csv/pnjs_en.csv");
    inf->atlases.icons = load_csv("csv/icons.csv");
    inf->atlases.menus_en = load_csv("csv/menus_en.csv");
    inf->atlases.menus_fr = load_csv("csv/menus_fr.csv");
    inf->atlases.poke_names = load_csv("csv/poke_names.csv");
    inf->atlases.items = load_csv("csv/items.csv");
    inf->atlases.item_sprites = load_csv("csv/items_sprite.csv");
}
