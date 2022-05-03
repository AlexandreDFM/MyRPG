/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** delete_quiz
*/

#include "rpg.h"
#include "quiz.h"

void delete_quiz(wininf *inf)
{
    free(inf->quiz);
    inf->quiz = NULL;
}
