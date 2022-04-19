/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** move_rect_intro
*/

#include "intro.h"

void move_rectintroleft(sfIntRect *rect, int modify, int max_value)
{
    if (rect->left >= max_value)
        rect->left = 4456 + 263;
    else
        rect->left += modify;
}

void move_rectintroleft2(sfIntRect *rect, int modify, int max_value)
{
    if (rect->left >= max_value)
        rect->left = 4456 + 40;
    else
        rect->left += modify;
}

void move_rectintroleft3(sfIntRect *rect, int modify, int max_value)
{
    if (rect->left >= max_value)
        rect->left = 4456 + 138;
    else
        rect->left += modify;
}

void move_rectintrotop(sfIntRect *rect, int modify, int max_value)
{
    if (rect->top <= max_value)
        rect->top = max_value;
    else
        rect->top -= modify;
}
