/*
** EPITECH PROJECT, 2022
** colored_text
** File description:
** dialog
*/

#ifndef DIALOG_H_
    #define DIALOG_H_

    #include <SFML/Graphics.h>

typedef struct dialog_line_t {
    int i;
    int max;
    int height;
    int *steps;
    float time;
    int nblines;
    int cline;
    sfSprite **sps;
    sfTexture *img;
} dline;

void load_alphabet(sfFont *font, int size);

#endif
