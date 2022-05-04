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
    qcm->destroy = 0; qcm->tendance = 0; qcm->nbquestions = 0;
    qcm->nature = my_malloc(sizeof(int) * 13);
    qcm->addptsnature = my_malloc(sizeof(int) * 13);
    for (int i = 0; i < 13; i++) {
        qcm->nature[i] = i; qcm->addptsnature[i] = 0;
    }
    for (int i = 0; i < 13; i++) qcm->nature[i] = 0;
    qcm->questions = load_csv("./csv/quiz_questions.csv");
    for (; qcm->questions[qcm->nbquestions] != NULL; qcm->nbquestions++);
    qcm->actualquestion = 1; qcm->aquestions = NULL;
    qcm->quizbox = generate_textbox((sfVector2i) {385, 50}, inf->atlases.atlas);
    sfSprite_setPosition(qcm->quizbox, (sfVector2f) {200, 720});
    sfSprite_setScale(qcm->quizbox, (sfVector2f) {4, 4});
    qcm->text = sfText_create();
    sfText_setFont(qcm->text, inf->ui.font);
    sfText_setCharacterSize(qcm->text, 80);
    sfText_setColor(qcm->text, sfColor_fromRGB(255, 255, 255));
    sfText_setPosition(qcm->text, (sfVector2f) {400, 750});
    sfText_setString(qcm->text, "Press R to answer yes, L to answer no");
    return qcm;
}
