/*
** EPITECH PROJECT, 2022
** B-MUL-200-NCE-2-1-myrpg-antoine.frankel
** File description:
** simple_maths
*/

#include "rpg.h"

float my_lerpf(float a, float b, float t)
{
    return a + (b - a) * t;
}
