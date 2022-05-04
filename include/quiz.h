/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** quiz
*/

#include "rpg.h"
#include "cinematics_elements.h"

#ifndef QUIZ_H_
    #define QUIZ_H_

enum nature {
    Hardy = 0,
    Docile = 1,
    Brave = 2,
    Jolly = 3,
    Impish = 4,
    Naive = 5,
    Timid = 6,
    Hasty = 7,
    Sassy = 8,
    Calm = 9,
    Relaxed = 10,
    Lonely = 11,
    Quirky = 12,
    HOMME = 13,
    FEMELLE = 14
};

typedef struct questions_quiz {
    sfText *question;
    sfText *answer1;
    int ptsanswer1;
    sfText *answer2;
    int ptsanswer2;
    struct questions_quiz *next;
} q_quiz;

typedef struct quiz_t {
    int clicked;
    int destroy;
    int tendance;
    int nbquestions;
    int actualquestion;
    int *nature;
    int *addptsnature;
    char **questions;
    char **aquestions;
    cine_ele cursor;
    sfSprite *quizbox;
    q_quiz *questions_quiz;
    q_quiz *actualquestion_quiz;
} quiz;

void handle_quiz(wininf *inf);
void delete_quiz(wininf *inf);
void quiz_choice(wininf *inf);
quiz *create_quiz(wininf *inf);
int chose_line(char **csv, int tendance, int sexe);
void move_cursor_quiz(wininf *inf, cine_ele *cursor);
q_quiz *create_questions_quiz(wininf *inf, char **csv, int nbquestions);

#endif /* !QUIZ_H_ */
