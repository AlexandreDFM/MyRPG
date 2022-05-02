/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** create_quiz
*/

#include "quiz.h"

quiz *create_quiz(wininf *inf)
{
    quiz *qcm = malloc(sizeof(quiz));
    qcm->destroy = 0;
    qcm->tendance = 0;
    qcm->nature = malloc(sizeof(int) * 13);
    for (int i = 0; i < 13; i++) qcm->nature[i] = 0;
    qcm->questions = load_csv("./csv/quiz_questions.csv"); qcm->nbquestions = 6;
    // for (; qcm->questions[qcm->nbquestions] != NULL; qcm->nbquestions++);
    qcm->actualquestion = 1;
    return qcm;
}
