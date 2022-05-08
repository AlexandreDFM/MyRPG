/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** draw_dungeons
*/

#include "rpg.h"

void perform_attack_mob(wininf *inf, player *e, player *p)
{
    if (e->time > 1.0f && e->attacking == 2) {
        e->attacking -= 1;
        int A = e->st.attack, B = e->st.lvl, C = p->st.defense;
        int D = ((A - C) / 8) + (B * 43690 / 65536);
        int dmg = floor((2 * D) - C + 10 + (D * D) * (3276 / 65536));
        p->st.health -= dmg < 0 ? -dmg : dmg;
        if (p->st.health <= 0) {
            add_log(inf, "%s%s</c> I'm not feeling well...\n", YELLOW,
                "Pokemon");
            inf->change_scene = 1;
            inf->dungeon.in = 0;
            inf->transition = 1; p->st.health = p->st.max_health;
            inf->next_pos = (sfVector2f){170.0f, 100.0f};
            inf->next_scene = INTERIOR;
        }
        else {
            add_log(inf, "Aie j'ai pris %d hp\n", dmg < 0 ? dmg * -1 : dmg);
        }
    }
}

void update_attack_anims(wininf *inf, player *e, player *p)
{
    sfVector2f ppos = sfSprite_getPosition(p->test);
    if (!is_same(ppos, p->nextpos, 1.0f) || !e->attacking) return;
    e->time += inf->time.dt * 6.0f;
    sfVector2f np = my_lerp(e->target, e->attack_pos,
        my_pingpong(e->time, 1.0f));
    p->can_move = 0;
    sfSprite_setPosition(e->test, np);
    perform_attack_mob(inf, e, p);
    if (e->time >= 2.0f) {
        e->attacking = 0;
        e->time = 0.0f;
        p->can_move = 1;
    }
}

void draw_dungeon(wininf *inf, player *p)
{
    if (inf->dungeon.ended) inf->dungeon.time += inf->time.dt;
    sfRenderWindow_drawSprite(inf->win, inf->dungeon.inf->sp, 0);
    sfRenderWindow_drawSprite(inf->win, inf->dungeon.inf->stairs, 0);
    for (list *t = inf->dungeon.enemies; t; t = t->next) {
        player *enemy = t->data;
        if (enemy->st.health <= 0) continue;
        sfVector2f np = my_lerp(sfSprite_getPosition(enemy->test),
            enemy->target, inf->time.dt * 6.0f);
        sfSprite_setPosition(enemy->test, np);
        if (is_same(np, enemy->target, 1.0f) && !enemy->arrived) {
            enemy->arrived = 1;
        }
        update_attack_anims(inf, enemy, p);
        player_direction_management(inf, enemy);
        sfRenderWindow_drawSprite(inf->win, enemy->test, enemy->shiny ?
        &(inf->state) : 0);
    }
}
