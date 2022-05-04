/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** quiz
*/

#include "rpg.h"
#include "quiz.h"
#include "dream.h"

int add_pts(wininf *inf, char *nature)
{
    for (int i = 0; i < 13; i++) {
        if (inf->quiz->nature[i] == my_atoi(nature)) return i;
    }
    return 0;
}

int chose_tendance(wininf *inf)
{
    int tendance = 0;
    int valtendance = inf->quiz->addptsnature[0];
    for (int i = 0; i < 13; i++) {
        if (valtendance < inf->quiz->addptsnature[i]) {
            tendance = i; valtendance = inf->quiz->addptsnature[i];
        }
    }
    return tendance;
}

void qcm(wininf *inf)
{
    if (inf->quiz->actualquestion >= inf->quiz->nbquestions) {
        inf->quiz->destroy = 1; return;
    }
    if (inf->quiz->aquestions == NULL) {
        inf->quiz->aquestions =
        my_strtwa(inf->quiz->questions[inf->quiz->actualquestion], ";\n");
        sfText_setString(inf->quiz->text, inf->quiz->aquestions[0]);
    }
    // if (inf->quiz->aquestions != NULL)
    //     for (int i = 0; inf->quiz->aquestions[i] != NULL; i++) 
    //         my_printf("%s\n", inf->quiz->aquestions[i]);
    if (inf->quiz->aquestions != NULL && sfKeyboard_isKeyPressed(sfKeyRControl)) {
        int idx = add_pts(inf, inf->quiz->aquestions[3]);
        inf->quiz->addptsnature[idx] += 1; inf->quiz->actualquestion += 1;
        my_free_array(inf->quiz->aquestions); inf->quiz->aquestions = NULL;
        // sleep(1);
    }
    if (inf->quiz->aquestions != NULL && sfKeyboard_isKeyPressed(sfKeyLControl)) {
        int idx = add_pts(inf, inf->quiz->aquestions[5]);
        inf->quiz->addptsnature[idx] += 1; inf->quiz->actualquestion += 1;
        my_free_array(inf->quiz->aquestions); inf->quiz->aquestions = NULL;
        // sleep(1);
    }
    sfRenderWindow_drawSprite(inf->win, inf->quiz->quizbox, NULL);
    sfRenderWindow_drawText(inf->win, inf->quiz->text, NULL);
}

void draw_quiz(wininf *inf, player *p)
{
    if (inf->quiz == NULL) inf->quiz = create_quiz(inf);
    draw_dream(inf);
    qcm(inf);
    if (inf->quiz->destroy == 1) {
        inf->quiz->sexe = 1;
        char **csv = load_csv("./csv/quiz_choices.csv");
        // my_printf("Pokemon : %d\n", inf->settings->pokemon);
        inf->quiz->tendance = chose_tendance(inf);
        inf->settings->pokemon = chose_line(csv, inf->quiz->tendance, inf->quiz->sexe);
        // my_printf("Pokemon Change : %d\n", inf->settings->pokemon);
        // my_printf("Print 1 :%d\n", p->r.width);
        *p = *(init_player(*(inf), inf->settings->pokemon));
        inf->camera.target = p->test;
        // my_printf("Print 2 :%d\n", p->r.width);
        // delete_quiz(inf); delete_dream(inf);
        inf->c_scene = MAIN_MENU;
    }
}
