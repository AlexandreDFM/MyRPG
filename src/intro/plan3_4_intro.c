/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** plan2_intro
*/

#include "rpg.h"
#include "intro.h"

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
        sfSprite_setColor(rpg->b_intro[3].sprite,
        (sfColor) {base.r, base.g, base.b, base.a + 5});
        if (base.a + 5 >= 255) rpg->plan = PLAN5;
        inf->time.intro_anim = 0.0f;
    }
}
