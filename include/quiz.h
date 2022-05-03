/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** quiz
*/

#include "rpg.h"

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
};

enum sexe {
    MALE = 0,
    FEMELLE = 1,
};

typedef struct quiz_t {
    int sexe;
    int destroy;
    int tendance;
    int nbquestions;
    int actualquestion;
    int *nature;
    char **questions;
} quiz;

void delete_quiz(wininf *inf);
quiz *create_quiz(wininf *inf);
int chose_line(char **csv, int tendance, int sexe);

#endif /* !QUIZ_H_ */
