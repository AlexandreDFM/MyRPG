/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** plan_intro
*/

#include "rpg.h"
#include "intro.h"

void plan0_clock(wininf *inf, intro_a *rpg)
{
    if (inf->time.intro_anim > 0.030f && rpg->plan == PLAN0) {
        rpg->pkmintro[RDMPKM].pos.y -= 7;
        if (rpg->pkmintro[RDMPKM].pos.y <= 550) {
            rpg->pkmintro[RDMPKM].rect.left = 0; rpg->plan = PLAN1;
            rpg->pkmintro[BEKIPAN2].rect = (sfIntRect) {92, 58, 28, 21};
        } inf->time.intro_anim = 0.0f;
    }
    if (inf->time.intro_anim2 > 0.25f && rpg->plan == PLAN0) {
        if (rpg->pkmintro[RDMPKM].rect.left >=
        rpg->pkmintro[RDMPKM].rect.width * 2) {
            rpg->pkmintro[RDMPKM].rect.left = 0;
        } else {
            rpg->pkmintro[RDMPKM].rect.left +=
            rpg->pkmintro[RDMPKM].rect.width;
        } move_rectintroleft2(&rpg->pkmintro[BEKIPAN1].rect, 31, 93);
        move_rectintroleft2(&rpg->pkmintro[BEKIPAN2].rect, 31, 93);
        inf->time.intro_anim2 = 0.0f;
    }
}

void plan5_clock(wininf *inf, intro_a *rpg)
{
    if (inf->time.intro_anim > 0.1f && rpg->plan == PLAN5) {
        sfMusic_pause(rpg->i_music1); sfMusic_play(rpg->i_music2);
        rpg->b_intro[0].rect = (sfIntRect) {480, 608, 240, 160};
        rpg->b_intro[1].rect = (sfIntRect) {480, 448, 240, 160};
        rpg->b_intro[0].pos = (sfVector2f) {120, -60};
        rpg->b_intro[2].rect = (sfIntRect) {720, 481, 96, 29};
        rpg->b_intro[2].pos = (sfVector2f) {645, 766};
        rpg->b_intro[3].rect = (sfIntRect) {1011, 483, 96, 29};
        rpg->b_intro[3].pos = (sfVector2f) {645, 942};
        rpg->b_intro[1].resize = (sfVector2f) {5, 5};
        rpg->b_intro[1].pos = (sfVector2f) {360, 0};
        sfColor base = sfSprite_getColor(rpg->b_intro[3].sprite);
        sfSprite_setColor(rpg->b_intro[3].sprite,
        (sfColor) {base.r, base.g, base.b, 255});
        rpg->valid = 2; rpg->plan = PLAN6; inf->time.intro_anim = 0.0f;
    }
}

void plan6_clock(wininf *inf, intro_a *rpg)
{
    if (inf->time.intro_anim > 0.06f && rpg->plan == PLAN6) {
        rpg->b_intro[0].rect.left += 1;
        inf->time.intro_anim = 0.0f;
    }
    if (inf->time.intro_anim2 > 0.1f && rpg->plan == PLAN6) {
        rpg->b_intro[2].rect.left += 97;
        rpg->b_intro[3].rect.left += 97;
        move_sun(rpg);
        move_sun_reverse(rpg);
        if (rpg->b_intro[0].rect.left >= 720)
            rpg->b_intro[0].rect.left = 480;
        inf->time.intro_anim2 = 0.0f;
    }
}

void plan_clock(sfRenderWindow *window, wininf *inf, intro_a *rpg)
{
    plan0_clock(inf, rpg);
    plan1_clock(inf, rpg);
    plan2_clock(inf, rpg);
    plan3_clock(inf, rpg);
    plan4_clock(inf, rpg);
    plan5_clock(inf, rpg);
    plan6_clock(inf, rpg);
}
