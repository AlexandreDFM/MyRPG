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
    sfTexture *img;
    sfSprite *sp;
    int *steps;
    int height;
    int i;
    int max;
    float time;
} dline;

void load_alphabet(sfFont *font, int size);

#endif
