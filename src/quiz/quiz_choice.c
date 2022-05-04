/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** quiz_choice
*/

#include "rpg.h"
#include "quiz.h"

int add_pts(wininf *inf, char *nature)
{
    for (int i = 0; i < 13; i++) {
        if (inf->quiz->nature[i] == my_atoi(nature)) return i;
    }
    return 0;
}

void quiz_choice(wininf *inf)
{
    int idx = 0;
    if (inf->quiz->clicked == 0 && inf->quiz->aquestions != NULL && inf->inputs.interact == 1) {
        if (inf->quiz->cursor.pos.x == 400)
            idx = add_pts(inf, inf->quiz->aquestions[3]);
        else
            idx = add_pts(inf, inf->quiz->aquestions[5]);
        inf->quiz->addptsnature[idx] += 1; inf->quiz->actualquestion += 1;
        my_free_array(inf->quiz->aquestions); inf->quiz->aquestions = NULL;
        inf->quiz->actualquestion_quiz = inf->quiz->actualquestion_quiz->next;
        inf->quiz->clicked = 1;
    }
}
