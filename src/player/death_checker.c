/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** player_movement
*/

#include "rpg.h"

void perform_attack(wininf *inf, player *p, sfVector2f pos)
{
    p->attack_pos = (sfVector2f){pos.x + p->vel.x * 24.0f,
        p->vel.y * 24.0f + pos.y};
    p->attacking = 2;
}

void check_death(wininf *inf, player *enemy, player *p)
{
    if (enemy->st.health <= 0) {
        p->can_move = 1;
        if (rand() % 10 > 5)
            add_to_inventory(inf, p->inv, rand() % 9);
    }
}
