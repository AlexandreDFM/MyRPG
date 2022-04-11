/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** inti_player
*/

#include "rpg.h"

player init_player(wininf inf, int id)
{
    player p;
    char **arr = my_strtwa(inf.atlases.pokemons_anim[id], ";\n");
    sfIntRect r = (sfIntRect){my_atoi(arr[1]), my_atoi(arr[2]),
        my_atoi(arr[3]), my_atoi(arr[4])};
    p.test = atlas_to_sprite(r, inf.atlases.atlas);
    p.speed = 120.0f;
    p.vel = (sfVector2f){0.0f, 0.0f};
    sfSprite_setOrigin(p.test, (sfVector2f){11.0f, 25.0f});
    sfSprite_setPosition(p.test, (sfVector2f){520.0f, 320.0f});
    return p;
}
