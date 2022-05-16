/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** perform_movement
*/

#include "rpg.h"
#include "sounds.h"

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

int handle_attack(wininf *inf, player *p)
{
    sfVector2f pos = sfSprite_getPosition(p->test);
    if (p->attacking) {
        p->time += inf->time.dt * 6.0f;
        sfVector2f np = my_lerp(p->nextpos, p->attack_pos,
        my_pingpong(p->time, 1.0f));
        sfSprite_setPosition(p->test, np);
        if (p->time >= 1.0f && p->attacking == 2) {
            deal_dmg(inf, p);
            p->attacking -= 1;
        }
        if (p->time >= 2.0f) {
            p->attacking = 0;
            p->time = 0.0f;
        } return 1;
    }
    if (inf->inputs.attack && inf->inputs.can_attack) {
        perform_attack(inf, p, pos);
        inf->inputs.can_attack = 0;
        return 1;
    } return 0;
}

int test_func(wininf *inf, player *p)
{
    for (list *t = inf->dungeon.enemies; t; t = t->next) {
        player *enemy = t->data;
        if (enemy->attacking) return 0;
    }
    return 1;
}

int next_floor(wininf *inf, player *p)
{
    sfVector2f pos = sfSprite_getPosition(p->test);
    sfVector2i lp = global_to_local(pos);
    sfVector2f center = local_to_global(lp.x, lp.y);
    map_inf *mapi = inf->dungeon.inf;
    int centered = is_same(center, pos, 1.0f);
    if (mapi->map[lp.y][lp.x] == 'F' && centered && !inf->dungeon.next) {
        sfSound_play(inf->sounds->sounds_board[STAIR_UP]);
        inf->transition = 1;
        inf->change_scene = -1;
        inf->next_pos = pos;
    }
    p->can_move = 1;
    return 0;
}

void perform_ifs_dungeon(wininf *inf, sfVector2i np, player *p, sfIntRect r)
{
    if (!is_same(inf->inputs.axis, (sfVector2f){0.0f, 0.0f}, 0.1f))
        p->vel = inf->inputs.axis;
    if (r.left && r.top && r.width && r.height && !inf->inputs.back) {
        p->nextpos = local_to_global(np.x, np.y);
        update_mobs(inf, p);
    }
}
