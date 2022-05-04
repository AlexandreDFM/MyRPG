/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** move_cursor_quiz
*/

#include "rpg.h"
#include "cinematics_elements.h"

void move_cursor_quiz(wininf *inf, cine_ele *cursor)
{
    if (cursor->pos.x == 1000 && inf->inputs.axis.x <= -0.5f) {
        cursor->pos.x = 400;
    }
    if (cursor->pos.x == 400 && inf->inputs.axis.x >= 0.5f) {
        cursor->pos.x = 1000;
    }
}
