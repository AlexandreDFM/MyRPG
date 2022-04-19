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
            rpg->pkmintro[RDMPKM].rect.left = 324;
            rpg->pkmintro[BEKIPAN2].rect = (sfIntRect) {4456 + 92, 58, 28, 21};
            rpg->plan = PLAN1;
        }
        inf->time.intro_anim = 0.0f;
    }
    if (inf->time.intro_anim2 > 0.25f && rpg->plan == PLAN0) {
        if (rpg->pkmintro[RDMPKM].rect.left >= 324 + 54)
            rpg->pkmintro[RDMPKM].rect.left = 324;
        else
            rpg->pkmintro[RDMPKM].rect.left += 27;
        move_rectintroleft2(&rpg->pkmintro[BEKIPAN1].rect, 31, 4456 + 93);
        move_rectintroleft2(&rpg->pkmintro[BEKIPAN2].rect, 31, 4456 + 93);
        inf->time.intro_anim2 = 0.0f;
    }
}

void plan1_clock(wininf *inf, intro_a *rpg)
{
    if (inf->time.intro_anim > 0.030f && rpg->plan == PLAN1) {
        if (rpg->b_intro[0].rect.top > 124) {
            move_rectintrotop(&rpg->b_intro[0].rect, 1, 124);
            rpg->pkmintro[RDMPKM].pos.y += 7;
            rpg->pkmintro[BEKIPAN2].pos.y += 7;
        } else if (rpg->b_intro[0].rect.top <= 124 && rpg->pkmintro[BEKIPAN1].pos.y >= -29){
            rpg->pkmintro[BEKIPAN1].pos.x += 7;
            rpg->pkmintro[BEKIPAN1].pos.y -= 4;
        } else {
            rpg->b_intro[0].rect = (sfIntRect) {4456 + 263, 201, 240, 160};
            rpg->pkmintro[BEKIPAN1].pos = (sfVector2f) {120 + 550, 250};
            rpg->plan = PLAN2;
        }
        inf->time.intro_anim = 0.0f;
    }
    if (inf->time.intro_anim2 > 0.25f && rpg->plan == PLAN1) {
        if (rpg->b_intro[0].rect.top > 124)
            move_rectintroleft2(&rpg->pkmintro[BEKIPAN1].rect, 31, 4456 + 93);
        else if (rpg->b_intro[0].rect.top == 124 && rpg->pkmintro[BEKIPAN1].rect.left != 4456 + 138) {
            rpg->pkmintro[BEKIPAN1].rect = (sfIntRect) {4456 + 138, 18, 29, 21};
            move_rectintrotop(&rpg->b_intro[0].rect, 1, 124);
        } else {
            if (rpg->pkmintro[BEKIPAN1].rect.left >= 4456 + 196)
                rpg->pkmintro[BEKIPAN1].rect.left = 4456 + 138;
            else
                rpg->pkmintro[BEKIPAN1].rect.left += 29;
        }
        if (rpg->pkmintro[BEKIPAN2].rect.left >= 4456 + 148)
            rpg->pkmintro[BEKIPAN2].rect.left = 4456 + 92;
        else
            rpg->pkmintro[BEKIPAN2].rect.left += 28;
        inf->time.intro_anim2 = 0.0f;
    }
}

void plan2_clock(wininf *inf, intro_a *rpg)
{
    if (inf->time.intro_anim > 0.05f && rpg->plan == PLAN2) {
        move_rectintroleft(&rpg->b_intro[1].rect, 1, 4456 + 529);
        rpg->pkmintro[BEKIPAN1].pos.x += 7;
        rpg->pkmintro[BEKIPAN1].pos.y -= 4;
        //if (rpg->b_intro[1].rect.left >= 4456 + 529) {
        if (rpg->pkmintro[BEKIPAN1].pos.y < (0 - (rpg->pkmintro[BEKIPAN1].rect.height * 7))) {
            rpg->b_intro[0].rect = (sfIntRect) {4456 + 0, 465, 240, 160};
            rpg->pkmintro[BEKIPAN1].pos = (sfVector2f) {222 * 7, 63};
            rpg->pkmintro[BEKIPAN1].resize = (sfVector2f) {1, 1};
            rpg->plan = PLAN3;
        }
        inf->time.intro_anim = 0.0f;
    }
    if (inf->time.intro_anim2 > 0.25f && rpg->plan == PLAN2) {
        move_rectintroleft(&rpg->b_intro[2].rect, 240, 4456 + 1223);
        if (rpg->pkmintro[BEKIPAN1].rect.left >= 4456 + 196)
            rpg->pkmintro[BEKIPAN1].rect.left = 4456 + 138;
        else 
            rpg->pkmintro[BEKIPAN1].rect.left += 29;
        inf->time.intro_anim2 = 0.0f;
    }
}

void plan3_clock(wininf *inf, intro_a *rpg)
{
    if (inf->time.intro_anim > 0.05f && rpg->plan == PLAN3) {
        move_rectintrotop(&rpg->b_intro[0].rect, 1, 124);
        rpg->pkmintro[BEKIPAN1].pos.x += 7;
        rpg->pkmintro[BEKIPAN1].pos.y += 7;
        rpg->pkmintro[BEKIPAN1].resize.x -= 0.1;
        rpg->pkmintro[BEKIPAN1].resize.y -= 0.1;
        if (rpg->b_intro[0].rect.top <= 465 - 56) {
            rpg->plan = PLAN4;
        }
        inf->time.intro_anim = 0.0f;
    }
}

void plan4_clock(wininf *inf, intro_a *rpg)
{
    if (inf->time.intro_anim > 0.05f && rpg->plan == PLAN4) {
        sfColor base = sfSprite_getColor(rpg->b_intro[3].sprite);
        sfSprite_setColor(rpg->b_intro[3].sprite, (sfColor) {base.r, base.g, base.b, base.a + 5});
        if (base.a + 5 >= 255) rpg->plan = PLAN5;
        inf->time.intro_anim = 0.0f;
    }
}

void plan5_clock(wininf *inf, intro_a *rpg)
{
    if (inf->time.intro_anim > 0.1f && rpg->plan == PLAN5) {
        sfMusic_pause(rpg->i_music1);
        sfMusic_play(rpg->i_music2);
        rpg->b_intro[0].rect = (sfIntRect) {4456 + 480, 608, 240, 160};
        rpg->b_intro[1].rect = (sfIntRect) {4456 + 480, 448, 240, 160};
        rpg->b_intro[2].rect = (sfIntRect) {4456 + 720, 481, 96, 29};
        rpg->b_intro[2].pos = (sfVector2f) {4456 + 120 + 75 * 7, 118 * 7};
        rpg->b_intro[3].rect = (sfIntRect) {4456 + 1011, 483, 96, 29};
        rpg->b_intro[3].pos = (sfVector2f) {4456 + 120 + 75 * 7, (118 + 28) * 7};
        rpg->valid = 2;
        rpg->plan = PLAN6;
        inf->time.intro_anim = 0.0f;
    }
}

void plan6_clock(wininf *inf, intro_a *rpg)
{
    if (inf->time.intro_anim > 0.1f && rpg->plan == PLAN6) {
        rpg->b_intro[0].rect.left += 1;
        inf->time.intro_anim = 0.0f;
    }
    if (inf->time.intro_anim2 > 0.5f && rpg->plan == PLAN6) {
        rpg->b_intro[2].rect.left += 97;
        rpg->b_intro[3].rect.left += 97;
        move_sun(rpg);
        move_sun_reverse(rpg);
        if (rpg->b_intro[0].rect.left >= 4456 + 720)
            rpg->b_intro[0].rect.left = 4456 + 480;
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
