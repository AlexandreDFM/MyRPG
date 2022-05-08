/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** player_movement
*/

#include "rpg.h"

void draw_shadow(wininf *inf, player *p)
{
    if (p->shadow == NULL) return;
    sfVector2f pos = sfSprite_getPosition(p->test);
    sfVector2f shadowpos = {pos.x - 8.0f, pos.y + 2.0f};
    sfSprite_setPosition(p->shadow, shadowpos);
    sfRenderWindow_drawSprite(inf->win, p->shadow, NULL);
}

void draw_player(wininf *inf, player *p)
{
    if (!inf->dungeon.in) {
        p->vel = inf->inputs.axis;
        if (inf->c_menu == NONE)
            perform_free_movement(inf, p);
    } else {
        perform_dungeon_movement(inf, p);
    }
    if (inf->net->is_multi && inf->net->other.p) {
        sfVector2f pos = sfSprite_getPosition(inf->net->other.p->test);
        pos = my_lerp(pos, inf->net->other.target, inf->time.dt * 40.0f);
        sfSprite_setPosition(inf->net->other.p->test, pos);
        if (inf->net->other.cscene == inf->c_scene)
            sfRenderWindow_drawSprite(inf->win, inf->net->other.p->test, 0);
    } update_camera(inf, p);
    sfShader_setFloatUniform((sfShader*)inf->state.shader, "time",
    inf->time.time);
    draw_shadow(inf, p);
    sfRenderWindow_drawSprite(inf->win, p->test, p->shiny ? &inf->state : 0);
}

int is_valid_move(wininf *inf, sfVector2i np, int target)
{
    int encountered = 0;
    for (list *t = inf->dungeon.enemies; t; t = t->next) {
        player *enemy = t->data;
        if (enemy->st.health <= 0) continue;
        sfVector2f tg = target ? enemy->target :
            sfSprite_getPosition(enemy->test);
        sfVector2i ep = global_to_local(tg);
        if (np.x == ep.x && np.y == ep.y)
            encountered++;
    }
    return encountered;
}

void deal_dmg(wininf *inf, player *p)
{
    for (list *t = inf->dungeon.enemies; t; t = t->next) {
        player *enemy = t->data;
        sfVector2f epos = sfSprite_getPosition(enemy->test);
        if (!is_same(p->attack_pos, epos, 12.0f)) continue;
        int A = p->st.attack, B = p->st.lvl, C = enemy->st.defense;
        int D = ((A - C) / 8) + (B * 43690 / 65536);
        int dmg = floor((2 * D) - C + 10 + (D * D) * (3276 / 65536));
        enemy->st.health -= dmg > 0 ? dmg : -dmg;
<<<<<<< HEAD
        int remain = enemy->st.health;
        add_log(inf, "Dealt: %d hp. The pokemon got %d remaining\n",
            dmg < 0 ? dmg * -1 : dmg, remain > 0 ? remain : 0);
        check_death(inf, enemy, p);
=======
        add_log(inf, "%s: %d hp. %s %d hp%s\n", inf->lang ? "Infliges" :
        "Dealt", dmg < 0 ? dmg * -1 : dmg, inf->lang ? "Il lui reste" :
        "The pokemon got", enemy->st.health, inf->lang ? "" : " remaining");
        if (enemy->st.health <= 0) p->can_move = 1;
>>>>>>> 004e7568f3aa8db5cfc70dcde07050914aabff55
    }
    update_mobs(inf, p);
}
