/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_dream
*/

#include "dream.h"
#include "ditto.h"

// 882 / 3 : 374 / 2

dream_a *create_dream(wininf *inf)
{
    dream_a *dream = malloc(sizeof(dream_a));
    dream->plan = DREAMINIT;
    dream->b_dream[0] = c_eles("dreams.png", (sfVector2f) {0, 0}, (sfIntRect) {0, 0, 882 / 3, 384});
    dream->b_dream[0].resize = (sfVector2f) {6.530612245, 5.625};
    dream->b_dream[1] = c_eles("dreams.png", (sfVector2f) {0, 0}, (sfIntRect) {882 / 3, 0, 882 / 3, 384});
    dream->b_dream[1].resize = (sfVector2f) {6.530612245, 5.625};
    dream->b_dream[2] = c_eles("dreams.png", (sfVector2f) {0, 0}, (sfIntRect) {882 / 3 + 882 / 3, 192, 882 / 3, 384});
    dream->b_dream[2].resize = (sfVector2f) {6.530612245, 5.625};
    dream->color = 0;
    dream->music = sfMusic_createFromFile("music/04_welcome_to_the_world_of_pokemon.ogg");
    return dream;
}
