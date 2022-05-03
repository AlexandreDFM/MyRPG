/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** quiz
*/

#include "rpg.h"
#include "quiz.h"
#include "dream.h"

void qcm(wininf *inf)
{
    if (inf->quiz->actualquestion >= inf->quiz->nbquestions) {
        inf->quiz->destroy = 1; return;
    }
    char **line = my_strtwa(inf->quiz->questions[inf->quiz->actualquestion], ";\n");
    // my_printf(("Line 1: %s\n"), line[0]);
    // my_printf(("Line 2: %s\n"), line[1]);
    // my_printf(("Line 3: %s\n"), line[2]);
    // my_printf(("Line 4: %s\n"), line[3]);
    // my_printf(("Line 5: %s\n"), line[4]);
    my_free_array(line);
    if (sfMouse_isButtonPressed(sfMouseLeft)) {
        inf->quiz->tendance += 1;
        inf->quiz->actualquestion += 1;
    }
    // my_printf("Actual Question : %d\n", inf->quiz->actualquestion);
}

void draw_quiz(wininf *inf, player *p)
{
    if (inf->quiz == NULL) inf->quiz = create_quiz(inf);
    draw_dream(inf);
    qcm(inf);
    if (inf->quiz->destroy == 1) {
        inf->quiz->sexe = 1;
        char **csv = load_csv("./csv/quiz_choices.csv");
        my_printf("Pokemon : %d\n", inf->settings->pokemon);
        inf->settings->pokemon = chose_line(csv,
        inf->quiz->tendance, inf->quiz->sexe);
        my_printf("Pokemon : %d\n", inf->settings->pokemon);
        inf->settings->pokemon = 6;
        delete_quiz(inf); delete_dream(inf); inf->c_scene = HOME;
    }
}
