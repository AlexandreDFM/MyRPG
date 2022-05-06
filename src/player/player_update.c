/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** player_movement
*/

#include "rpg.h"

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
    } update_camera(inf);
    sfShader_setFloatUniform((sfShader*)inf->state.shader, "time",
    inf->time.time);
    sfRenderWindow_drawSprite(inf->win, p->test, p->shiny ? &inf->state : 0);
}

void perform_free_movement(wininf *inf, player *p)
{
    sfVector2f po = sfSprite_getPosition(p->test);
    sfVector2f nextp = (sfVector2f){po.x, po.y};
    list *cols = inf->scenes[inf->c_scene].colls;
    nextp.x += p->vel.x; nextp.y += p->vel.y;
    sfVector2f np = my_lerp(po, nextp, p->speed * inf->time.dt);
    sfFloatRect rect = (sfFloatRect){np.x, np.y, p->vel.x, p->vel.y};
    if (inf->c_scene != DUNGEON)
        if (!(is_valid(cols, &rect, inf, p) && !inf->transition))
            return;
    sfSprite_setPosition(p->test, np);
    if (!is_same(np, p->sentpos, 1.0f) && inf->net->is_multi) {
        p->sentpos = np;
        add_ord(POSITION, &np, sizeof(sfVector2f), inf->net->packet);
    }
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

void perform_attack(wininf *inf, player *p, sfVector2f pos)
{
    p->attack_pos = (sfVector2f){pos.x + p->vel.x * 24.0f,
        p->vel.y * 24.0f + pos.y};
    p->attacking = 2;
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
        enemy->st.health -= dmg;
        add_log(inf, "Dealt: %d hp\n", dmg < 0 ? dmg * -1 : dmg, enemy->st.health);
    }
}

void perform_dungeon_movement(wininf *inf, player *p)
{
    sfVector2f pos = sfSprite_getPosition(p->test);
    if (p->attacking) {
        p->time += inf->time.dt * 6.0f;
        sfVector2f np = my_lerp(p->nextpos, p->attack_pos, my_pingpong(p->time, 1.0f));
        sfSprite_setPosition(p->test, np);
        if (p->time >= 1.0f && p->attacking == 2) {
            deal_dmg(inf, p);
            p->attacking -= 1;
        }
        if (p->time >= 2.0f) {
            p->attacking = 0;
            p->time = 0.0f;
        }
        return;
    }
    if (inf->inputs.attack && inf->inputs.can_attack) {
        perform_attack(inf, p, pos);
        inf->inputs.can_attack = 0;
        return;
    }
    sfVector2f axis = inf->inputs.axis;
    sfVector2f input = (sfVector2f){pos.x + axis.x * 24.0f,
        axis.y * 24.0f + pos.y};
    sfVector2i np = global_to_local(input);
    sfVector2i target = global_to_local(p->nextpos);
    int cond = is_same(axis, (sfVector2f){0.0f, 0.0f}, 0.3f);
    int cond2 = is_same(pos, p->nextpos, 2.0f);
    if (!(inf->dungeon.inf->map[np.y]) ||
        np.x > my_strlen(inf->dungeon.inf->map[0]) - 1) return;
    char c = inf->dungeon.inf->map[np.y][np.x];
    int walkable = c == ' ' || c == 'E';
    sfVector2f newp = my_lerp(pos, p->nextpos, inf->time.dt * 4.0f);
    sfSprite_setPosition(p->test, newp);
    int valid = !is_valid_move(inf, np, 0);
    int poscond = (np.x != target.x || np.y != target.y) && valid;
    if (!is_same(inf->inputs.axis, (sfVector2f){0.0f, 0.0f}, 0.1f))
        p->vel = inf->inputs.axis;
    if (walkable && !cond && cond2 && poscond && !inf->inputs.back) {
        p->nextpos = local_to_global(np.x, np.y);
        update_mobs(inf, p);
    }
}
