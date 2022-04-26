/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_intro
*/

#include "intro.h"

void move_sun(intro_a *rpg)
{
    if (rpg->b_intro[2].rect.top == 481 && rpg->b_intro[2].rect.left >= 4456 + 914) {
        rpg->b_intro[2].rect.top = 513;
        rpg->b_intro[2].rect.left = 4456 + 720;
    }
    if (rpg->b_intro[2].rect.top == 513 && rpg->b_intro[2].rect.left >= 4456 + 914) {
        rpg->b_intro[2].rect.top = 545;
        rpg->b_intro[2].rect.left = 4456 + 914;
    }
    if (rpg->b_intro[2].rect.top == 545 && rpg->b_intro[2].rect.left >= 4456 + 914) {
        rpg->b_intro[2].rect.top = 577;
        rpg->b_intro[2].rect.left = 4456 + 720;
    }
    if (rpg->b_intro[2].rect.top == 577 && rpg->b_intro[2].rect.left >= 4456 + 914) {
        rpg->b_intro[2].rect.top = 481;
        rpg->b_intro[2].rect.left = 4456 + 720;
    }
}

void move_sun_reverse(intro_a *rpg)
{
    if (rpg->b_intro[3].rect.top == 483 && rpg->b_intro[3].rect.left >= 4456 + 1205) {
        rpg->b_intro[3].rect.top = 515;
        rpg->b_intro[3].rect.left = 4456 + 1011;
    }
    if (rpg->b_intro[3].rect.top == 515 && rpg->b_intro[3].rect.left >= 4456 + 1205) {
        rpg->b_intro[3].rect.top = 547;
        rpg->b_intro[3].rect.left = 4456 + 1011;
    }
    if (rpg->b_intro[3].rect.top == 547 && rpg->b_intro[3].rect.left >= 4456 + 1205) {
        rpg->b_intro[3].rect.top = 579;
        rpg->b_intro[3].rect.left = 4456 + 1011;
    }
    if (rpg->b_intro[3].rect.top == 579 && rpg->b_intro[3].rect.left >= 4456 + 1205) {
        rpg->b_intro[3].rect.top = 483;
        rpg->b_intro[3].rect.left = 4456 + 1011;
    }
}

intro_a *create_intro(wininf *inf)
{
    intro_a *intro = malloc(sizeof(intro_a));
    intro->plan = PLAN0;
    intro->valid = 0;
    sfVector2f size = {7, 7};
    // intro->pkmintro[0] = c_ele(inf->atlases.atlas, (sfVector2f) {120 + 560, 1080}, (sfIntRect) {4456 + 0, 41, 24, 19}, size);
    intro->pkmintro[0] = c_ele(inf->atlases.atlas, (sfVector2f) {120 + 560, 1080}, (sfIntRect) {324, 1232, 27, 22}, size);    
    intro->pkmintro[1] = c_ele(inf->atlases.atlas, (sfVector2f) {120 + 550, 250}, (sfIntRect) {4456 + 40, 16, 31, 26}, size);
    intro->pkmintro[2] = c_ele(inf->atlases.atlas, (sfVector2f) {120 + 950, 250}, (sfIntRect) {4456 + 40, 16, 31, 26}, size);
    intro->pkmintro[3] = c_ele(inf->atlases.atlas, (sfVector2f) {120 + 560, 1080}, (sfIntRect) {4456 + 0, 41, 24, 19}, size);
    intro->b_intro[0] = c_ele(inf->atlases.atlas, (sfVector2f) {120, 0}, (sfIntRect) {4456 + 2, 224, 240, 160}, size);
    // intro->b_intro[0] = c_ele(inf->atlases.atlas, (sfVector2f) {120, 0}, (sfIntRect) {1232, 855, 10, 8}, size);
    intro->b_intro[1] = c_ele(inf->atlases.atlas, (sfVector2f) {120, 0}, (sfIntRect) {4456 + 263, 7, 240, 160}, size);
    intro->b_intro[2] = c_ele(inf->atlases.atlas, (sfVector2f) {120, 574}, (sfIntRect) {4456 + 263, 88, 240, 104}, size);
    intro->b_intro[3] = c_ele(inf->atlases.atlas, (sfVector2f) {120, 0}, (sfIntRect) {4456 + 240, 408, 240, 160}, size);
    sfColor base = sfSprite_getColor(intro->b_intro[3].sprite);
    sfSprite_setColor(intro->b_intro[3].sprite, (sfColor) {base.r, base.g, base.b, 0});
    intro->i_music1 = sfMusic_createFromFile("music/01_pkm_red_rescue_team_theme.ogg");
    intro->i_music2 = sfMusic_createFromFile("music/02_title_screen.ogg");
    return intro;
}
