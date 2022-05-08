/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** manage_quest
*/

#include "rpg.h"
#include "sounds.h"

void manage_quest(wininf *inf)
{
    if (inf->quest == 1) {
        sfSound_play(inf->sounds->sounds_board[BIG_REWARD]);
        inf->quest = 3;
    }
}
