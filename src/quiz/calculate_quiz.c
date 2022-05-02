/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** calculate_quiz
*/

#include "quiz.h"

int quiz_result(char **csv, int sexe, int line)
{
    char **tab = my_strtwa(csv[line], ";\n");
    int pokemon = (sexe == MALE ? my_atoi(tab[1]) : my_atoi(tab[2])); 
    my_free_array(tab);
    my_printf("My Calculate PKM : %d\n", pokemon);
    return pokemon;
}

int chose_line(char **csv, int tendance, int sexe)
{
    if (tendance == Hardy) return quiz_result(csv, sexe, 1);
    if (tendance == Docile) return quiz_result(csv, sexe, 2);
    if (tendance == Brave) return quiz_result(csv, sexe, 3);
    if (tendance == Jolly) return quiz_result(csv, sexe, 4);
    if (tendance == Impish) return quiz_result(csv, sexe, 5);
    if (tendance == Naive) return quiz_result(csv, sexe, 6);
    if (tendance == Timid) return quiz_result(csv, sexe, 7);
    if (tendance == Hasty) return quiz_result(csv, sexe, 8);
    if (tendance == Sassy) return quiz_result(csv, sexe, 9);
    if (tendance == Calm) return quiz_result(csv, sexe, 10);
    if (tendance == Relaxed) return quiz_result(csv, sexe, 11);
    if (tendance == Lonely) return quiz_result(csv, sexe, 12);
    if (tendance == Quirky) return quiz_result(csv, sexe, 13);
}
