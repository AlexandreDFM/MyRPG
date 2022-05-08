/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** perform_movement
*/

#include "rpg.h"

void perform_dungeon_movement(wininf *inf, player *p)
{
    if (!(p->can_move) || next_floor(inf, p)) return;
    if (handle_attack(inf, p)) return;
    sfVector2f pos = sfSprite_getPosition(p->test);
    sfVector2f axis = inf->inputs.axis;
    sfVector2f input = (sfVector2f){pos.x + axis.x * 24.0f,
        axis.y * 24.0f + pos.y};
    sfVector2i np = global_to_local(input);
    sfVector2i target = global_to_local(p->nextpos);
    int cond = is_same(axis, (sfVector2f){0.0f, 0.0f}, 0.3f);
    int cond2 = is_same(pos, p->nextpos, 2.0f) && test_func(inf, p);
    char c = inf->dungeon.inf->map[np.y][np.x];
    int walkable = c == ' ' || c == 'E' || c == 'F';
    sfVector2f newp = my_lerp(pos, p->nextpos, inf->time.dt * 4.0f);
    sfSprite_setPosition(p->test, newp);
    int valid = !is_valid_move(inf, np, 0);
    int poscond = (np.x != target.x || np.y != target.y) && valid;
    perform_ifs_dungeon(inf, np, p, (sfIntRect){walkable, !cond, cond2,
        poscond});
}
