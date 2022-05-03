/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** plan1_intro
*/

#include "rpg.h"
#include "intro.h"

void plan1_clock2(wininf *inf, intro_a *rpg)
{
    if (rpg->b_intro[0].rect.top > 124) {
        move_rectintroleft2(&rpg->pkmintro[BEKIPAN1].rect, 31, 93);
    } else if (rpg->b_intro[0].rect.top == 124 &&
        rpg->pkmintro[BEKIPAN1].rect.left != 138) {
        rpg->pkmintro[BEKIPAN1].rect = (sfIntRect) {138, 18, 29, 21};
        move_rectintrotop(&rpg->b_intro[0].rect, 1, 124);
    } else {
        if (rpg->pkmintro[BEKIPAN1].rect.left >= 196)
            rpg->pkmintro[BEKIPAN1].rect.left = 138;
        else
            rpg->pkmintro[BEKIPAN1].rect.left += 29;
    }
    if (rpg->pkmintro[BEKIPAN2].rect.left >= 148)
        rpg->pkmintro[BEKIPAN2].rect.left = 92;
    else
        rpg->pkmintro[BEKIPAN2].rect.left += 28;
    inf->time.intro_anim2 = 0.0f;
}

void plan1_clock(wininf *inf, intro_a *rpg)
{
    if (inf->time.intro_anim > 0.030f && rpg->plan == PLAN1) {
        if (rpg->b_intro[0].rect.top > 124) {
            move_rectintrotop(&rpg->b_intro[0].rect, 1, 124);
            rpg->pkmintro[RDMPKM].pos.y += 7;
            rpg->pkmintro[BEKIPAN2].pos.y += 7;
        } else if (rpg->b_intro[0].rect.top <= 124 &&
        rpg->pkmintro[BEKIPAN1].pos.y >= -29){
            rpg->pkmintro[BEKIPAN1].pos.x += 7;
            rpg->pkmintro[BEKIPAN1].pos.y -= 4;
        } else {
            rpg->b_intro[0].rect = (sfIntRect) {263, 201, 240, 160};
            rpg->pkmintro[BEKIPAN1].pos = (sfVector2f) {120 + 550, 250};
            rpg->plan = PLAN2;
        }
        inf->time.intro_anim = 0.0f;
    }
    if (inf->time.intro_anim2 > 0.25f && rpg->plan == PLAN1) {
        plan1_clock2(inf, rpg);
    }
}

void plan2_clock2(wininf *inf, intro_a *rpg)
{
    if (inf->time.intro_anim2 > 0.25f && rpg->plan == PLAN2) {
        move_rectintroleft(&rpg->b_intro[2].rect, 240, 1223);
        if (rpg->pkmintro[BEKIPAN1].rect.left >= 196)
            rpg->pkmintro[BEKIPAN1].rect.left = 138;
        else
            rpg->pkmintro[BEKIPAN1].rect.left += 29;
        inf->time.intro_anim2 = 0.0f;
    }
}

void plan2_clock(wininf *inf, intro_a *rpg)
{
    if (inf->time.intro_anim > 0.05f && rpg->plan == PLAN2) {
        move_rectintroleft(&rpg->b_intro[1].rect, 1, 529);
        rpg->pkmintro[BEKIPAN1].pos.x += 7;
        rpg->pkmintro[BEKIPAN1].pos.y -= 4;
        if (rpg->pkmintro[BEKIPAN1].pos.y < (0 -
        (rpg->pkmintro[BEKIPAN1].rect.height * 7))) {
            rpg->b_intro[0].rect = (sfIntRect) {0, 465, 240, 160};
            rpg->pkmintro[BEKIPAN1].pos = (sfVector2f) {222 * 7, 63};
            rpg->pkmintro[BEKIPAN1].resize = (sfVector2f) {1, 1};
            rpg->plan = PLAN3;
        }
        inf->time.intro_anim = 0.0f;
    }
    plan2_clock2(inf, rpg);
}
