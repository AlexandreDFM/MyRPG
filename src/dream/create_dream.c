/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_dream
*/

#include "dream.h"
#include "ditto.h"

dream_a *create_dream(wininf *inf)
{
    dream_a *dream = malloc(sizeof(dream_a));
    dream->plan = DREAMINIT;
    // dream->b_dream[0] = c_eles("dreams_1.png", (sfVector2f) {0, 0}, (sfIntRect) {0, 0, 882 / 3, 384});
    // dream->b_dream[0].resize = (sfVector2f) {6.530612245, 5.625};
    // dream->b_dream[1] = c_eles("dreams_1.png", (sfVector2f) {0, 0}, (sfIntRect) {882 / 3, 0, 882 / 3, 384});
    // dream->b_dream[1].resize = (sfVector2f) {6.530612245, 5.625};
    // dream->b_dream[2] = c_eles("dreams_1.png", (sfVector2f) {0, 0}, (sfIntRect) {882 / 3 + 882 / 3, 192, 882 / 3, 384});
    // dream->b_dream[2].resize = (sfVector2f) {6.530612245, 5.625};
    for (int i = 0, j = 1; i < 3; i++, j++) {
        dream->b_dream[i] = c_ele(inf->atlases.atlas, "./csv/dreams.csv", j);
    }
    dream->color = 0;
    sfColor changecolor = my_hsvtorgb(dream->color, 50, 100);
    for (int i = 0; i < 3; i++) {
        sfSprite_setColor(dream->b_dream[i].sprite, changecolor);
    }
    dream->music =
    sfMusic_createFromFile("music/04_welcome_to_the_world_of_pokemon.ogg");
    sfMusic_setLoop(dream->music, sfTrue);
    return dream;
}
