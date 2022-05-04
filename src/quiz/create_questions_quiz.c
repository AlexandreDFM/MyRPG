/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_questions_quiz
*/

#include "quiz.h"

sfText *create_answer(wininf *inf, char *answer, sfVector2f posb)
{
    sfText *text = sfText_create();
    sfText_setFont(text, inf->ui.font);
    sfText_setCharacterSize(text, 80);
    sfText_setString(text, answer);
    sfText_setPosition(text, posb);
    sfText_setColor(text, sfWhite);
    return text;
}

void link_questions_quiz(q_quiz *q1, q_quiz *q2)
{
    q1->next = q2;
}

q_quiz *create_question_full(wininf *inf, char *csv)
{
    q_quiz *question = malloc(sizeof(q_quiz));
    char **linecsv = my_strtwa(csv, ";\n");
    question->question = sfText_create();
    sfText_setString(question->question, linecsv[0]);
    sfText_setFont(question->question, inf->ui.font);
    sfText_setCharacterSize(question->question, 80);
    sfFloatRect size = sfText_getGlobalBounds(question->question);
    sfText_setOrigin(question->question, (sfVector2f) {size.width / 2, size.height / 2});
    sfText_setPosition(question->question, (sfVector2f) {970, 750});
    sfText_setColor(question->question, sfWhite);
    question->answer1 = create_answer(inf, linecsv[1], (sfVector2f) {440, 810});
    question->answer2 = create_answer(inf, linecsv[2], (sfVector2f) {1040, 810});
    question->next = NULL;
    my_free_array(linecsv);
    return question;
}

q_quiz *create_questions_quiz(wininf *inf, char **csv, int nbquestions)
{
    q_quiz *questions = NULL; q_quiz *question_tmp = NULL;
    q_quiz *question_tmp2 = NULL;
    for (int i = 0; i < nbquestions; i++) {
        question_tmp = create_question_full(inf, csv[i]);
        if (i == 0) questions = question_tmp;
        else link_questions_quiz(question_tmp2, question_tmp);
        question_tmp2 = question_tmp;
    }
    return questions;
}
