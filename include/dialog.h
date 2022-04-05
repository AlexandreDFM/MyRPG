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
    int *steps;
    int height;
    int i;
    float time;
} dline;

void load_alphabet(sfFont *font, int size);
void treat_balise(char *balise, sfColor *color);
dline *load_line(char *line, sfFont *font, int size);

#endif /* !DIALOG_H_ */
